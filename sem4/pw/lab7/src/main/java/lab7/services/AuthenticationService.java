package lab7.services;

import lab7.entities.User;
import lab7.entities.Session;
import lab7.repositories.UserRepository;
import org.springframework.stereotype.Service;
import org.apache.commons.lang.RandomStringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;

import java.util.Arrays;
import java.util.Optional;
import javax.servlet.http.Cookie;
import javax.transaction.Transactional;
import javax.servlet.http.HttpServletRequest;

@Service
@Transactional
public class AuthenticationService
{
    private final UserRepository userRepository;
    private final BCryptPasswordEncoder passwordEncoder;

    @Autowired
    public AuthenticationService(UserRepository userRepository, BCryptPasswordEncoder passwordEncoder)
    {
        this.userRepository = userRepository;
        this.passwordEncoder = passwordEncoder;
    }

    public String generateSessionString()
    {
        return RandomStringUtils.randomAlphanumeric(255);
    }

    public String setUserSession(String username)
    {
        User user = this.userRepository.findByUsername(username);
        if(user.getSession() == null)
        {
            Session newSession = new Session();
            newSession.setToken(generateSessionString());
            user.setSession(newSession);
        }
        else
        {
            user.getSession().setToken(generateSessionString());
        }
        userRepository.save(user);
        return user.getSession().getToken();
    }

    public boolean registerUser(String username, String password)
    {
        if (userRepository.findByUsername(username) != null)
        {
            return false;
        }
        User newUser = new User();
        newUser.setUsername(username);
        newUser.setPasswordHash(passwordEncoder.encode(password));
        userRepository.save(newUser);
        return true;
    }

    public boolean loginUser(String username, String password)
    {
        User user = userRepository.findByUsername(username);
        if (user == null)
        {
            return false;
        }
        return passwordEncoder.matches(password, user.getPasswordHash());
    }

    public Optional<User> validateRequest(HttpServletRequest request)
    {
        Optional<Cookie> sessionOptional = Arrays.stream(request.getCookies())
                .filter(c -> c.getName().equals("session"))
                .findAny();
        if(sessionOptional.isEmpty()) return Optional.empty();
        Cookie sessionCookie = sessionOptional.get();
        return this.userRepository.findBySessionToken(sessionCookie.getValue());
    }
}
