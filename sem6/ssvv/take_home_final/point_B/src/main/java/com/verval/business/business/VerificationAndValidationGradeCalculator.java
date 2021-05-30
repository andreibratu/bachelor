package com.verval.business.business;

import com.verval.business.exception.InvalidPointException;
import com.verval.business.model.GradeType;
import com.verval.business.model.Point;

import java.util.ArrayList;
import java.util.Optional;

public class VerificationAndValidationGradeCalculator {
    private  ArrayList<Point> points;
    private String studentId;

    public VerificationAndValidationGradeCalculator() {
        points = new ArrayList<Point>();
        points.add(new Point(10,10, GradeType.Granted));
    }

    public ArrayList<Point> getPoints() {
        return points;
    }

    public String getStudentId() {
        return studentId;
    }

    public void setStudentId(String studentId) {
        this.studentId = studentId;
    }


    public void addPoint(Point point) {
        validatePoint(point);
        points.add(point);
    }

    public double getGrade() {
        return points.stream().mapToDouble(Point::getPoint).sum() / 10;
    }

    // Task B_1
    // Validate the value of the point, it needs to be in the interval of [0,10]
    // If the point is invalid throw InvalidPointException
    private void validatePoint(Point point) throws InvalidPointException {
        if (point.getPoint() < 0 || point.getPoint() > 10)
            throw  new InvalidPointException("Invalid point value");
        if (point.getPoint() > point.getMaxPoint())
            throw new InvalidPointException("Point larger than max value");
        if (point.getMaxPoint() < 1 || point.getMaxPoint() > 10)
            throw new InvalidPointException("Illegal max point value");
        switch (point.getType()) {
            case Exam:
                Optional<Point> exam = points.stream().filter((p) -> p.getType().equals(GradeType.Exam)).findFirst();
                if (exam.isPresent()) throw new InvalidPointException("Exam point already exists");
                break;
            case Granted:
                throw new InvalidPointException("Granted point cannot be added by user");
            default:
                break;
        }

    }

    private double getPointsSumOfType(GradeType type) {
        return points.stream().filter(point->point.getType() == type)
                .mapToDouble(point->point.getPoint()).sum();
    }

    // Task B_2
    // Conditions for a passing grade are listed below
    // The sum of the laboratory grades needs to be greater than 10
    // The sum of the seminar grades needs to be greater than 10
    // There can only one exam grade be added
    // The grade calculated with the getGrade function needs to be greater or equal to 5
	public boolean isPassing() {
        double sumLab = points.stream()
                .filter(p -> p.getType() == GradeType.Laboratory)
                .mapToDouble(Point::getPoint)
                .sum();
        double sumSeminar = points.stream()
                .filter(p -> p.getType() == GradeType.Seminar)
                .mapToDouble(Point::getPoint)
                .sum();
        // Validation already prevents more than one Exam grade
        boolean hasExam = points.stream().anyMatch(p -> p.getType() == GradeType.Exam);
        return sumLab > 10 && sumSeminar > 10 && hasExam && getGrade() >= 5;
    }


}
