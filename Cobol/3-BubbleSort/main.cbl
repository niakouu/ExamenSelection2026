       IDENTIFICATION DIVISION.
       PROGRAM-ID. BUBBLE-SORT.

       DATA DIVISION.
       WORKING-STORAGE SECTION.

       01  NUMBERS-TABLE.
           05  NUM        PIC 9(3) OCCURS 5 TIMES.

       PROCEDURE DIVISION.
           MOVE 50 TO NUM(1).
           MOVE 30 TO NUM(2).
           MOVE 10 TO NUM(3).
           MOVE 40 TO NUM(4).
           MOVE 20 TO NUM(5).

           DISPLAY "Before sorting:".
           PERFORM VARYING I FROM 1 BY 1 UNTIL I > 5
               DISPLAY NUM(I)
           END-PERFORM.

        *>    PERFORM BUBBLE-SORT-PARA.

           DISPLAY "After sorting:".
           PERFORM VARYING I FROM 1 BY 1 UNTIL I > 5
               DISPLAY NUM(I)
           END-PERFORM.

           STOP RUN.

    *>    BUBBLE-SORT-PARA.

    *>    END-PERFORM.
