package server.controllers;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.junit.Before;
import org.junit.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.springframework.http.MediaType;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.setup.MockMvcBuilders;
import server.controllers.entity.ClientController;
import server.dtos.ClientDTO;
import server.entities.Client;
import server.services.entity.ClientEntityServiceImplementation;
import server.validators.ClientValidator;

import java.util.Arrays;
import java.util.List;
import java.util.Optional;

import static org.hamcrest.CoreMatchers.anyOf;
import static org.hamcrest.Matchers.hasSize;
import static org.hamcrest.core.Is.is;
import static org.mockito.Mockito.*;
import static org.mockito.MockitoAnnotations.initMocks;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;

public class ClientControllerTest
{
    private MockMvc mockMvc;

    @InjectMocks
    private ClientController clientController;

    @Mock
    private ClientEntityServiceImplementation clientService;

    @Mock
    private ClientValidator clientValidator;

    private Client client1;
    private Client client2;

    @Before
    public void setup()
    {
        initMocks(this);
        this.mockMvc = MockMvcBuilders
                .standaloneSetup(clientController)
                .build();
        initData();
    }

    private void initData()
    {
        client1 = Client.builder().address("a1").name("n1").build();
        client1.setId(1L);
        client2 = Client.builder().address("a2").name("n2").build();
        client2.setId(2L);
    }

    private String toJsonString(ClientDTO movieDTO)
    {
        try {
            return new ObjectMapper().writeValueAsString(movieDTO);
        } catch (JsonProcessingException e) {
            throw new RuntimeException(e);
        }
    }

    @Test
    public void getClients() throws Exception
    {
        List<Client> clients = Arrays.asList(client1, client2);

        when(clientService.getAllEntities(0)).thenReturn(clients);

        mockMvc
                .perform(MockMvcRequestBuilders.get("/clients"))
                .andExpect(status().isOk())
                .andExpect(content().contentType(MediaType.APPLICATION_JSON_UTF8))
                .andExpect(jsonPath("$", hasSize(2)))
                .andExpect(jsonPath("$[0].name", anyOf(is("n1"), is("n2"))))
                .andExpect(jsonPath("$[1].address", anyOf(is("a1"), is("a2"))));

        verify(clientService, times(1)).getAllEntities(0);
        verifyNoMoreInteractions(clientService, clientValidator);

    }

    @Test
    public void updateClient() throws Exception
    {

        when(clientService.updateEntity(client1)).thenReturn(java.util.Optional.ofNullable(client1));
        doNothing().when(clientValidator).validate(client1);

        mockMvc
                .perform(MockMvcRequestBuilders
                        .put("/clients/{clientId}", client1.getId(), client1.toDTO())
                        .contentType(MediaType.APPLICATION_JSON_UTF8)
                        .content(toJsonString(client1.toDTO())))

                .andExpect(status().isOk())
                .andExpect(content().contentType(MediaType.APPLICATION_JSON_UTF8))
                .andExpect(jsonPath("$.address", is("a1")));

        verify(clientService, times(1)).updateEntity(client1);
    }

    @Test
    public void addClient() throws Exception{
        when(clientService.addEntity(client1)).thenReturn(client1);
        doNothing().when(clientValidator).validate(client1);

        mockMvc
                .perform(MockMvcRequestBuilders
                        .post("/clients", client1.toDTO())
                        .contentType(MediaType.APPLICATION_JSON_UTF8)
                        .content(toJsonString(client1.toDTO())))

                .andExpect(status().isOk())
                .andExpect(content().contentType(MediaType.APPLICATION_JSON_UTF8))
                .andExpect(jsonPath("$.address", is("a1")));

    }

    @Test
    public void deleteClient() throws Exception
    {
        when(clientService.deleteEntity(client1.getId())).thenReturn(
                java.util.Optional.ofNullable(client1)
        );

        mockMvc
                .perform(MockMvcRequestBuilders
                        .delete("/clients/{clientId}", client1.getId())
                        .contentType(MediaType.APPLICATION_JSON_UTF8)
                        .content(client1.getId().toString()))
                .andExpect(status().isOk());
    }
}
