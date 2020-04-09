package common.entities;

import javax.persistence.Entity;
import java.io.Serializable;
import java.time.LocalDate;

@Entity
public class Rental extends BaseEntity<Long> implements Serializable
{
    private Long clientID;

    private Long movieID;

    private LocalDate startDate;

    private LocalDate endDate;

    public Rental()
    {
    }

    public Rental(Long clientID, Long movieID)
    {
        this.clientID = clientID;
        this.movieID = movieID;
        this.startDate = LocalDate.now();
        this.endDate = null;
    }

    public Rental(Long clientID, Long movieID, LocalDate startDate, LocalDate endDate)
    {
        this.clientID = clientID;
        this.movieID = movieID;
        this.startDate = startDate;
        this.endDate = endDate;
    }

    public Rental(Long id, Long clientID, Long movieID, LocalDate startDate)
    {
        this.setId(id);
        this.clientID = clientID;
        this.movieID = movieID;
        this.startDate = startDate;
    }

    public Rental(Long id, Long clientID, Long movieID, LocalDate startDate, LocalDate endDate)
    {
        this.setId(id);
        this.clientID = clientID;
        this.movieID = movieID;
        this.startDate = startDate;
        this.endDate = endDate;
    }

    public Long getClientID()
    {
        return clientID;
    }

    public Long getMovieID()
    {
        return movieID;
    }

    public LocalDate getStartDate()
    {
        return startDate;
    }

    public void returnMovie(LocalDate returnDate)
    {
        endDate = returnDate;
    }

    public LocalDate getEndDate()
    {
        return endDate;
    }

    @Override
    public boolean equals(Object o)
    {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Rental rental = (Rental) o;

        if (!clientID.equals(rental.clientID)) return false;
        if (!movieID.equals(rental.movieID)) return false;
        if (!startDate.equals(rental.startDate)) return false;
        return endDate.equals(rental.endDate);
    }

    @Override
    public String toString()
    {
        return "Rental{" +
                "clientID= '" + clientID + '\'' +
                ", movieID= '" + movieID + '\'' +
                ", startDate= '" + startDate + '\'' +
                ", endDate= '" + endDate + '\'' +
                "} " + super.toString();
    }
}
