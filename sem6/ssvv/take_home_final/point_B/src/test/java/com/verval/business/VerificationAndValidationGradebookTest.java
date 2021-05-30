package com.verval.business;

import com.verval.business.business.VerificationAndValidationGradeCalculator;
import com.verval.business.exception.InvalidPointException;
import com.verval.business.model.GradeType;
import com.verval.business.model.Point;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class VerificationAndValidationGradebookTest {

    private VerificationAndValidationGradeCalculator gradeCalculator;

    @BeforeEach
    void setup() {
        gradeCalculator = new VerificationAndValidationGradeCalculator();
    }

    @Test
    public void validatePoint_addingExamTwiceThrowsTest() {
        gradeCalculator.addPoint(new Point(8, 10, GradeType.Exam));
        assertThrows(InvalidPointException.class, () -> gradeCalculator.addPoint(new Point(7, 10, GradeType.Exam)));
    }

    @Test
    public void validatePoint_addingExamOnceTest() {
        assertEquals(gradeCalculator.getPoints().size(), 1L);
        gradeCalculator.addPoint(new Point(8, 10, GradeType.Exam));
        assertEquals(gradeCalculator.getPoints().size(), 2L);
    }

    @Test
    public void validatePoint_outOfBoundsTest() {
        assertThrows(
            InvalidPointException.class,
            () -> gradeCalculator.addPoint(new Point(-2, 10, GradeType.Seminar)));
        assertThrows(
            InvalidPointException.class,
            () -> gradeCalculator.addPoint(new Point(13, 10, GradeType.Seminar)));
    }

    @Test
    public void validatePoint_boundsTest() {
        assertEquals(gradeCalculator.getPoints().size(), 1L);
        gradeCalculator.addPoint(new Point(0, 10, GradeType.Laboratory));
        assertEquals(gradeCalculator.getPoints().size(), 2L);
        gradeCalculator.addPoint(new Point(10, 10, GradeType.Laboratory));
        assertEquals(gradeCalculator.getPoints().size(), 3L);
    }

    @Test
    public void validatePoint_addGrantedTest() {
        assertThrows(
            InvalidPointException.class,
            () -> gradeCalculator.addPoint(new Point(10, 10, GradeType.Granted))
        );
    }

    @Test
    public void validatePoint_maxPointOutBoundsTest() {
        assertThrows(
            InvalidPointException.class,
            () -> gradeCalculator.addPoint(new Point(6, 13, GradeType.Seminar)));
        assertThrows(
            InvalidPointException.class,
            () -> gradeCalculator.addPoint(new Point(5, 0, GradeType.Seminar)));
        assertThrows(
            InvalidPointException.class,
            () -> gradeCalculator.addPoint(new Point(5, -7, GradeType.Seminar)));
    }

    @Test
    public void validatePoint_pointLargerMaxValue() {
        assertThrows(
            InvalidPointException.class,
            () -> gradeCalculator.addPoint(new Point(11, 8, GradeType.Bonuses)));
    }

    @Test
    public void isPassing_noLaboratoryTest() {
        for (int i = 0; i < 10; i++)
            gradeCalculator.addPoint(new Point(10, 10, GradeType.Bonuses));
        for (int i = 0; i < 2; i++)
            gradeCalculator.addPoint(new Point(10, 10, GradeType.Seminar));
        gradeCalculator.addPoint(new Point(8, 10, GradeType.Exam));
        assertFalse(gradeCalculator.isPassing());
    }

    @Test
    public void isPassing_insufficientLabTest() {
        for (int i = 0; i < 10; i++)
            gradeCalculator.addPoint(new Point(10, 10, GradeType.Bonuses));
        for (int i = 0; i < 2; i++)
            gradeCalculator.addPoint(new Point(10, 10, GradeType.Seminar));
        gradeCalculator.addPoint(new Point(8, 10, GradeType.Exam));
        gradeCalculator.addPoint(new Point(10, 10, GradeType.Laboratory));
        assertFalse(gradeCalculator.isPassing());
    }

    @Test
    public void isPassing_noSeminarTest() {
        for (int i = 0; i < 10; i++)
            gradeCalculator.addPoint(new Point(10, 10, GradeType.Bonuses));
        for (int i = 0; i < 2; i++)
            gradeCalculator.addPoint(new Point(10, 10, GradeType.Laboratory));
        gradeCalculator.addPoint(new Point(8, 10, GradeType.Exam));
        assertFalse(gradeCalculator.isPassing());
    }

    @Test
    public void isPassing_insufficientSeminarTest() {
        for (int i = 0; i < 10; i++)
            gradeCalculator.addPoint(new Point(10, 10, GradeType.Bonuses));
        for (int i = 0; i < 2; i++)
            gradeCalculator.addPoint(new Point(10, 10, GradeType.Laboratory));
        gradeCalculator.addPoint(new Point(8, 10, GradeType.Exam));
        gradeCalculator.addPoint(new Point(10, 10, GradeType.Seminar));
        assertFalse(gradeCalculator.isPassing());
    }

    @Test
    public void isPassing_noExamTest() {
        for (int i = 0; i < 10; i++)
            gradeCalculator.addPoint(new Point(10, 10, GradeType.Bonuses));
        for (int i = 0; i < 2; i++)
            gradeCalculator.addPoint(new Point(10, 10, GradeType.Laboratory));
        for (int i = 0; i < 2; i++)
            gradeCalculator.addPoint(new Point(10, 10, GradeType.Seminar));
        assertFalse(gradeCalculator.isPassing());
    }

    @Test
    public void isPassing_noPassingGrade() {
        gradeCalculator.addPoint(new Point(10, 10, GradeType.Seminar));
        gradeCalculator.addPoint(new Point(10, 10, GradeType.Laboratory));
        gradeCalculator.addPoint(new Point(1, 10, GradeType.Seminar));
        gradeCalculator.addPoint(new Point(1, 10, GradeType.Laboratory));
        gradeCalculator.addPoint(new Point(2, 10, GradeType.Exam));
        assertFalse(gradeCalculator.isPassing());
    }

    @Test
    public void isPassing_passingGrade() {
        for (int i = 0; i < 10; i++) {
            gradeCalculator.addPoint(new Point(10, 10, GradeType.Seminar));
            gradeCalculator.addPoint(new Point(10, 10, GradeType.Laboratory));
        }
        gradeCalculator.addPoint(new Point(10, 10, GradeType.Exam));
        assertTrue(gradeCalculator.isPassing());
    }
}
