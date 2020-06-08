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
import server.controllers.entity.MovieController;
import server.dtos.MovieDTO;
import server.entities.GenreEnum;
import server.entities.Movie;
import server.services.entity.MovieEntityServiceImplementation;
import server.validators.MovieValidator;

import java.util.Arrays;
import java.util.List;
import java.util.Optional;

import static org.hamcrest.CoreMatchers.anyOf;
import static org.hamcrest.Matchers.hasSize;
import static org.hamcrest.core.Is.is;
import static org.mockito.Mockito.*;
import static org.mockito.MockitoAnnotations.initMocks;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;

public class MovieControllerTest
{
    private MockMvc mockMvc;

    @InjectMocks
    private MovieController movieController;

    @Mock
    private MovieEntityServiceImplementation movieService;

    @Mock
    private MovieValidator movieValidator;

    private Movie movie1;
    private Movie movie2;

    @Before
    public void setup() {
        initMocks(this);
        this.mockMvc = MockMvcBuilders
                .standaloneSetup(movieController)
                .build();
        initData();
    }

    private void initData() {
        movie1 = Movie.builder().title("tit1").genre(GenreEnum.ACTION).year(1997).build();
        movie1.setId(1L);
        movie2 = Movie.builder().title("tit2").genre(GenreEnum.COMEDY).year(2000).build();
        movie2.setId(2L);
    }

    @Test
    public void getMovies() throws Exception
    {
        List<Movie> movies = Arrays.asList(movie1, movie2);
        doNothing().when(movieValidator).validate(movie1);
        doNothing().when(movieValidator).validate(movie2);
        when(movieService.getAllEntities(0)).thenReturn(movies);

        mockMvc
                .perform(MockMvcRequestBuilders.get("/movies"))
                .andExpect(status().isOk())
                .andExpect(content().contentType(MediaType.APPLICATION_JSON_UTF8))
                .andExpect(jsonPath("$", hasSize(2)))
                .andExpect(jsonPath("$[0].title", anyOf(is("tit1"), is("tit2"))))
                .andExpect(jsonPath("$[1].genre", anyOf(is("ACTION"), is("COMEDY"))));


        verify(movieService, times(1)).getAllEntities(0);
    }

    @Test
    public void updateMovie() throws Exception{

        when(movieService.updateEntity(movie1)).thenReturn(java.util.Optional.ofNullable(movie1));
        doNothing().when(movieValidator).validate(movie1);
        doNothing().when(movieValidator).validate(movie2);

        mockMvc
                .perform(MockMvcRequestBuilders
                        .put("/movies/{movieId}", movie1.getId(), movie1.toDTO())
                        .contentType(MediaType.APPLICATION_JSON_UTF8)
                        .content(toJsonString((MovieDTO)movie1.toDTO())))

                .andExpect(status().isOk())
                .andExpect(content().contentType(MediaType.APPLICATION_JSON_UTF8))
                .andExpect(jsonPath("$.title", is("tit1")));

        verify(movieService, times(1)).updateEntity(movie1);
    }

    private String toJsonString(MovieDTO movieDTO)
    {
        try {
            return new ObjectMapper().writeValueAsString(movieDTO);
        } catch (JsonProcessingException e) {
            throw new RuntimeException(e);
        }
    }

    @Test
    public void addMovie() throws Exception
    {
        when(movieService.addEntity(movie1)).thenReturn(movie1);
        doNothing().when(movieValidator).validate(movie1);
        doNothing().when(movieValidator).validate(movie2);

        mockMvc
                .perform(MockMvcRequestBuilders
                        .post("/movies", movie1.toDTO())
                        .contentType(MediaType.APPLICATION_JSON_UTF8)
                        .content(toJsonString((MovieDTO) movie1.toDTO())))

                .andExpect(status().isOk())
                .andExpect(content().contentType(MediaType.APPLICATION_JSON_UTF8))
                .andExpect(jsonPath("$.title", is("tit1")));
    }

    @Test
    public void deleteMovie() throws Exception
    {
        when(movieService.deleteEntity(movie1.getId())).thenReturn(
                java.util.Optional.ofNullable(movie1)
        );

        mockMvc
                .perform(MockMvcRequestBuilders
                        .delete("/movies/{movieId}", movie1.getId())
                        .contentType(MediaType.APPLICATION_JSON_UTF8)
                        .content(movie1.getId().toString()))
                .andExpect(status().isOk());
    }

    @Test
    public void deleteNotExistingMovie() throws Exception
    {
        when(movieService.deleteEntity(42L)).thenReturn(Optional.empty());

        mockMvc
                .perform(MockMvcRequestBuilders
                        .delete("/movies/{movieId}", movie1.getId())
                        .contentType(MediaType.APPLICATION_JSON_UTF8)
                        .content(movie1.getId().toString()))
                .andExpect(status().isBadRequest());
    }
}
