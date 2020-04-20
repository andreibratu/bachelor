package common.entities;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.time.LocalDate;

import static org.junit.Assert.assertEquals;

public class RentalTest
{
    private static final Long ID = 1L;

    private static final Long CLIENT_ID = 1L;
    private static final Long MOVIE_ID = 1L;
    private static final LocalDate START_DATE = LocalDate.parse("2020-04-01");
    private static final LocalDate END_DATE = LocalDate.parse("2020-04-02");
    private static final LocalDate RETURN_DATE = LocalDate.parse("2020-04-03");

    private Rental rental;

    @Before
    public void setUp()
    {
        rental = new Rental(ID, CLIENT_ID, MOVIE_ID, START_DATE, END_DATE);
    }

    @After
    public void tearDown()
    {
        rental = null;
    }

    @Test
    public void testGetClientID()
    {
        assertEquals("Client Ids should be equal!", (long) CLIENT_ID, (long) rental.getClientID());
    }


    @Test
    public void testGetMovieID()
    {
        assertEquals("Movie Ids should be equal!", (long) MOVIE_ID, (long) rental.getMovieID());
    }

    @Test
    public void testGetStartDate()
    {
        assertEquals("Start dates should be equal!", START_DATE, rental.getStartDate());
    }

    @Test
    public void testGetEndDate()
    {
        assertEquals("End dates should be equal!", END_DATE, rental.getEndDate());
    }

    @Test
    public void testReturnMovie()
    {
        rental.returnMovie(RETURN_DATE);
        assertEquals("Return dates should be equal!", RETURN_DATE, rental.getEndDate());
    }
}
