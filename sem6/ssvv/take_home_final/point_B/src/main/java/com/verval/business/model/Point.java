package com.verval.business.model;

public class Point {
    private double point;
    private double maxPoint;
    private GradeType type;

    public Point(double point, double maxPoint, GradeType type) {
        this.point = point;
        this.maxPoint = maxPoint;
        this.type = type;
    }

    public double getPoint() {
        return point;
    }

    public double getMaxPoint() {
        return maxPoint;
    }

    public GradeType getType() {
        return type;
    }
}