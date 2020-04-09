package common.entities;

import javax.persistence.Entity;
import java.io.Serializable;

@Entity
public class Movie extends BaseEntity<Long> implements Serializable
{
    private String title;

    private GenreEnum genre;

    private Integer year;

    public Movie()
    {
    }

    public Movie(Long id, String title, GenreEnum genre, Integer year)
    {
        this.setId(id);
        this.title = title.trim();
        this.genre = genre;
        this.year = year;
    }

    public Movie(String title, GenreEnum genre, Integer year)
    {
        this.title = title.trim();
        this.genre = genre;
        this.year = year;
    }


    public String getTitle()
    {
        return title;
    }

    public void setTitle(String title)
    {
        this.title = title;
    }

    public GenreEnum getGenre()
    {
        return genre;
    }

    public void setGenre(GenreEnum genre)
    {
        this.genre = genre;
    }

    public Integer getYear()
    {
        return year;
    }

    public void setYear(Integer year)
    {
        this.year = year;
    }

    @Override
    public boolean equals(Object o)
    {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Movie movie = (Movie) o;

        if (genre != movie.genre) return false;
        if (!year.equals(movie.year)) return false;
        return title.equals(movie.title);

    }

    @Override
    public String toString()
    {
        return "Movie{" +
                "title= '" + title + '\'' +
                ", genre= '" + genre + '\'' +
                ", year= '" + year + '\'' +
                "} " + super.toString();
    }
}
