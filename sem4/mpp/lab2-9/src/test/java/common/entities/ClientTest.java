package common.entities;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class ClientTest {
    private static final Long ID = 1L;

    private static final String NAME = "Client_Name";
    private static final String NEW_NAME = "NEW_Client_Name";
    private static final String ADDRESS = "StreetNumberApartment";
    private static final String NEW_ADDRESS = "New_StreetNumberApartment";


    private Client client;

    @Before
    public void setUp() {
        client = new Client(NAME, ADDRESS);
        client.setId(ID);
    }

    @After
    public void tearDown() {
        client=null;
    }

    @Test
    public void testGetName() {
        assertEquals("Names should be equal!",NAME, client.getName());
    }

    @Test
    public void testSetName() {
        client.setName(NEW_NAME);
        assertEquals("Names should be equal!",NEW_NAME, client.getName());
    }

    @Test
    public void testGetAddress() {
        assertEquals("Addresses should be equal!",ADDRESS, client.getAddress());
    }

    @Test
    public void testSetAddress() {
        client.setAddress(NEW_ADDRESS);
        assertEquals("Addresses should be equal!",NEW_ADDRESS, client.getAddress());

    }

}
