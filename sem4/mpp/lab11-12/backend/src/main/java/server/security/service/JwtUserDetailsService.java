package server.security.service;

import java.util.ArrayList;

import server.security.dto.UserDTO;
import server.security.model.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;
import server.security.repository.UserRepository;

@Service
public class JwtUserDetailsService implements UserDetailsService
{
    private final UserRepository userRepository;

    private final PasswordEncoder bcryptEncoder;

    @Autowired
    public JwtUserDetailsService(UserRepository userRepository, PasswordEncoder bcryptEncoder)
    {
        this.userRepository = userRepository;
        this.bcryptEncoder = bcryptEncoder;
    }

    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException
    {
        User user = userRepository.findUserByUsername(username);
        if (user == null)
        {
            throw new UsernameNotFoundException("User not found with username: " + username);
        }
        return new org.springframework.security.core.userdetails.User(
                user.getUsername(), user.getPassword(), new ArrayList<>()
        );
    }

    public User save(UserDTO user)
    {
        User newUser = new User();
        newUser.setUsername(user.getUsername());
        newUser.setPassword(bcryptEncoder.encode(user.getPassword()));
        return userRepository.save(newUser);
    }
}