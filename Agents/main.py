"""
Robot Rescue Challenge - Main Runner

Use this script to test your solution against various maps.
"""

from grid import Grid
from robot import run_simulation
from maps import ALL_MAPS
from solution import solve


def run_all_tests():
    """Run the solution against all test maps."""
    print("=" * 60)
    print("Robot Rescue Challenge - Test Runner")
    print("=" * 60)
    print()

    results = []

    for name, map_str in ALL_MAPS.items():
        print(f"Testing map: {name}")
        print("-" * 40)

        try:
            grid = Grid.from_string(map_str)
            result = run_simulation(grid, solve)

            status = "✓ PASSED" if result.success else "✗ FAILED"
            print(f"  Status: {status}")
            print(f"  People saved: {result.people_saved}/{result.total_people}")
            print(f"  Time elapsed: {result.time_elapsed} seconds")
            print(f"  Message: {result.message}")

            results.append((name, result))

        except Exception as e:
            print(f"  ✗ ERROR: {str(e)}")
            results.append((name, None))

        print()

    # Summary
    print("=" * 60)
    print("Summary")
    print("=" * 60)

    passed = sum(1 for _, r in results if r and r.success)
    total = len(results)
    total_time = sum(r.time_elapsed for _, r in results if r and r.success)

    print(f"Maps passed: {passed}/{total}")
    if passed > 0:
        print(f"Total time (successful maps): {total_time} seconds")


def run_single_map(map_name: str):
    """Run the solution against a single map."""
    if map_name not in ALL_MAPS:
        print(f"Unknown map: {map_name}")
        print(f"Available maps: {', '.join(ALL_MAPS.keys())}")
        return

    map_str = ALL_MAPS[map_name]
    grid = Grid.from_string(map_str)

    print(f"Grid ({grid.width}x{grid.height}):")
    print(grid)
    print()

    result = run_simulation(grid, solve)

    print(f"Result: {'SUCCESS' if result.success else 'FAILED'}")
    print(f"People saved: {result.people_saved}/{result.total_people}")
    print(f"Time elapsed: {result.time_elapsed} seconds")
    print(f"Message: {result.message}")


if __name__ == "__main__":
    import sys

    if len(sys.argv) > 1:
        run_single_map(sys.argv[1])
    else:
        run_all_tests()
