package server.entities;

import lombok.*;

import java.io.Serializable;

@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
@EqualsAndHashCode
class RentalKey implements Serializable
{
    private Client client;
    private Movie movie;
}
