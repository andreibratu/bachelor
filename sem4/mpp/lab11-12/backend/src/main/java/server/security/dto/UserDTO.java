package server.security.dto;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import server.dtos.DTO;
import server.dtos.Transferable;
import server.security.model.User;

import java.io.Serializable;

@Data
@Builder
@AllArgsConstructor
public class UserDTO implements DTO<User>
{
    private String username;
    private String password;
}