package server.entities;

import lombok.AllArgsConstructor;
import lombok.Getter;

import java.io.Serializable;

@Getter
@AllArgsConstructor
public enum GenreEnum implements Serializable
{
    COMEDY("COMEDY"),
    ACTION("ACTION"),
    THRILLER("THRILLER"),
    DOCUMENTARY("DOCUMENTARY"),
    HORROR("HORROR"),
    ROMANTIC("ROMANTIC");

    private final String genre;
}
