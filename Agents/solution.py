"""
Robot Rescue Challenge - Solution Template

Implement your solution in the `solve` function below.
Your goal is to rescue the person trapped in the building as quickly as possible.

Available Robot methods:
    - robot.move(Direction) -> bool: Move in a direction (FORWARD, BACKWARD, LEFT, RIGHT)
    - robot.sense_fires_around() -> int: Get count of fires in adjacent cells (only cardinal directions, no diagonals) (does not cost time)
    - robot.scan_fires() -> Set[Position]: Get fire positions in cells around the robot (costs 10 seconds)
    - robot.position -> Position: Current robot position
    - robot.is_carrying_person -> bool: Whether robot is carrying someone
    - robot.get_grid_dimensions() -> Tuple[int, int]: Get (width, height)
    - robot.get_exit_position() -> Position: Get exit position
    - robot.get_person_position() -> Position: Get the person's position (known location)

Movement costs:
    - Each move: 1 second
    - Scan: 10 seconds

Rules:
    - There is exactly one person to rescue
    - The person's location is known from the start
    - Stepping on fire destroys the robot (mission fails immediately)
    - Robot starts at the exit position
    - Person is picked up automatically when robot reaches their cell
    - Mission ends automatically when robot returns to exit with the person

Objective: Navigate to the person, pick them up, and return to the exit as quickly as possible!
"""

from robot import Robot, Direction, Position


def solve(robot: Robot) -> None:
    """
    Implement your rescue algorithm here.

    Args:
        robot: The robot instance to control

    Note:
        The mission ends automatically when you return to the exit with the person.
        If the robot steps on fire, the mission fails immediately.
    """
    # TODO: Implement your solution here

    # Example: Get grid info
    width, height = robot.get_grid_dimensions()
    exit_pos = robot.get_exit_position()
    person_pos = robot.get_person_position()

    # Navigate to person and return to exit - mission ends automatically!
    prev_position : Position | None = None
    prev_prev_position : Position | None = None
    path = []
    prev_lookup = {}
    
    while robot.position != exit_pos or not robot.is_carrying_person:
        fire_count = robot.sense_fires_around()

        if not robot.is_carrying_person:
            path.append(robot.position)

        target : Position | None
        if robot.is_carrying_person:
            target = path.pop()
        else:
            target = person_pos

        if not robot.is_carrying_person and fire_count > 0:
            if prev_lookup[f'{robot.position.x}{robot.position.y}'] == None:
                prev_lookup[f'{robot.position.x}{robot.position.y}'] = robot.scan_fires(); 
            
            possible_positions = [Position(robot.position.x+1, robot.position.y),
                                Position(robot.position.x-1, robot.position.y),
                                Position(robot.position.x, robot.position.y+1),
                                Position(robot.position.x, robot.position.y-1)]
            
            best_pos : Position = None
            for position in possible_positions:
                if position.x < 0 or position.y < 0 or position.x > (width-1) or position.y > (height-1) or position in prev_lookup[f'{robot.position.x}{robot.position.y}']:
                    possible_positions.remove(position)
                if best_pos == None or distance(best_pos, target) > distance(position, target):
                    best_pos = position
                
            if best_pos.x == robot.position.x+1:
                robot.move(Direction.RIGHT)
            elif best_pos.x == robot.position.x-1:
                robot.move(Direction.LEFT)
            elif best_pos.y == robot.position.y+1:
                robot.move(Direction.BACKWARD)
            elif best_pos.y == robot.position.y-1:
                robot.move(Direction.FORWARD)
            print(possible_positions)
            print(height)
            print(width)
            print(best_pos)
            print(robot.position)
            print(robot.is_carrying_person)
            print(fire_count)
        elif robot.is_carrying_person:
            if target.x == robot.position.x+1:
                robot.move(Direction.RIGHT)
            elif target.x == robot.position.x-1:
                robot.move(Direction.LEFT)
            elif target.y == robot.position.y+1:
                robot.move(Direction.BACKWARD)
            elif target.y == robot.position.y-1:
                robot.move(Direction.FORWARD)
        else:
            x_distance = robot.position.x - target.x
            y_distance = robot.position.y - target.y
            if prev_prev_position != None:
                if x_distance > 0 and prev_prev_position.x != robot.position.x+1:
                    robot.move(Direction.LEFT)
                elif x_distance < 0 and prev_prev_position.x != robot.position.x-1:
                    robot.move(Direction.RIGHT)
                elif y_distance > 0 and prev_prev_position.y != robot.position.y+1:
                    robot.move(Direction.FORWARD)
                elif y_distance < 0 and prev_prev_position.y != robot.position.y-1:
                    robot.move(Direction.BACKWARD)
            else:
                if x_distance > 0:
                    robot.move(Direction.LEFT)
                elif x_distance < 0:
                    robot.move(Direction.RIGHT)
                elif y_distance > 0:
                    robot.move(Direction.FORWARD)
                elif y_distance < 0:
                    robot.move(Direction.BACKWARD)

        prev_prev_position = prev_position
        prev_position = robot.position

    return

def distance(position1, position2):
    return (position1.x - position2.x)**2 + (position1.y - position2.y)**2

def positionToString(position) :
    return f'{position.x}{position.y}'