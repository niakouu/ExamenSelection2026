"""
Robot Rescue Challenge - Grid

This module provides the Grid class representing the building layout
where the robot operates.
"""

from enum import Enum
from typing import Optional, Set, List
from dataclasses import dataclass


class CellType(Enum):
    """Types of cells in the grid."""

    EMPTY = "."
    FIRE = "F"
    PERSON = "P"
    EXIT = "E"


@dataclass
class Position:
    """Represents a position on the grid."""

    x: int
    y: int

    def __hash__(self):
        return hash((self.x, self.y))

    def __eq__(self, other):
        if isinstance(other, Position):
            return self.x == other.x and self.y == other.y
        return False


class Grid:
    """
    Represents the building grid where the robot operates.
    """

    def __init__(self, width: int, height: int):
        """
        Initialize an empty grid.

        Args:
            width: Width of the grid
            height: Height of the grid
        """
        self.width = width
        self.height = height
        self._cells: List[List[CellType]] = [
            [CellType.EMPTY for _ in range(width)] for _ in range(height)
        ]
        self._exit_position: Optional[Position] = None
        self._fire_positions: Set[Position] = set()
        self._person_positions: Set[Position] = set()

    def set_cell(self, x: int, y: int, cell_type: CellType) -> None:
        """Set the type of a cell."""
        if not self.is_valid_position(x, y):
            raise ValueError(f"Position ({x}, {y}) is outside the grid")

        pos = Position(x, y)

        # Remove from previous tracking sets
        self._fire_positions.discard(pos)
        self._person_positions.discard(pos)
        if self._exit_position == pos:
            self._exit_position = None

        self._cells[y][x] = cell_type

        # Add to appropriate tracking set
        if cell_type == CellType.FIRE:
            self._fire_positions.add(pos)
        elif cell_type == CellType.PERSON:
            self._person_positions.add(pos)
        elif cell_type == CellType.EXIT:
            self._exit_position = pos

    def get_cell(self, x: int, y: int) -> CellType:
        """Get the type of a cell."""
        if not self.is_valid_position(x, y):
            raise ValueError(f"Position ({x}, {y}) is outside the grid")
        return self._cells[y][x]

    def is_valid_position(self, x: int, y: int) -> bool:
        """Check if a position is within the grid bounds."""
        return 0 <= x < self.width and 0 <= y < self.height

    @property
    def exit_position(self) -> Optional[Position]:
        """Get the exit position."""
        return self._exit_position

    @property
    def fire_positions(self) -> Set[Position]:
        """Get all fire positions (for internal use)."""
        return self._fire_positions.copy()

    @property
    def person_positions(self) -> Set[Position]:
        """Get all person positions (for internal use)."""
        return self._person_positions.copy()

    def remove_person(self, pos: Position) -> bool:
        """Remove a person from the grid (when picked up)."""
        if pos in self._person_positions:
            self._person_positions.discard(pos)
            self._cells[pos.y][pos.x] = CellType.EMPTY
            return True
        return False

    @classmethod
    def from_string(cls, grid_string: str) -> "Grid":
        """
        Create a grid from a string representation.

        Legend:
            . = Empty cell
            F = Fire
            P = Person
            E = Exit

        Example:
            '''
            . . . . .
            . F . P .
            . . . . .
            . P . F .
            E . . . .
            '''
        """
        lines = [
            line.strip() for line in grid_string.strip().split("\n") if line.strip()
        ]
        height = len(lines)

        # Parse first line to get width
        first_row = lines[0].split()
        width = len(first_row)

        grid = cls(width, height)

        for y, line in enumerate(lines):
            cells = line.split()
            if len(cells) != width:
                raise ValueError(f"Row {y} has {len(cells)} cells, expected {width}")

            for x, cell_char in enumerate(cells):
                cell_type = CellType(cell_char)
                grid.set_cell(x, y, cell_type)

        if grid.exit_position is None:
            raise ValueError("Grid must have exactly one exit (E)")

        return grid

    def __str__(self) -> str:
        """String representation of the grid."""
        rows = []
        for y in range(self.height):
            row = " ".join(self._cells[y][x].value for x in range(self.width))
            rows.append(row)
        return "\n".join(rows)
