package server.security.model;

import com.fasterxml.jackson.annotation.JsonIgnore;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.NoArgsConstructor;
import server.dtos.DTO;
import server.dtos.Transferable;
import server.entities.BaseEntity;
import server.security.dto.UserDTO;

import javax.persistence.*;
import java.io.Serializable;

@Data
@Entity
@NoArgsConstructor
@AllArgsConstructor
@Table(name = "users")
@EqualsAndHashCode(callSuper = true)
public class User extends BaseEntity<Long> implements Serializable, Transferable<User>
{
    @Column(unique = true)
    private String username;

    @Column
    @JsonIgnore
    private String password;

    @Override
    public DTO<User> toDTO()
    {
        return UserDTO.builder()
                .username(username)
                .build();
    }
}
