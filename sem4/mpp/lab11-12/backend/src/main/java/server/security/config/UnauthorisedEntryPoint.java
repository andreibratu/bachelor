package server.security.config;

import java.io.IOException;
import java.io.Serializable;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.security.core.AuthenticationException;
import org.springframework.security.web.AuthenticationEntryPoint;
import org.springframework.stereotype.Component;

@Component
public class UnauthorisedEntryPoint implements AuthenticationEntryPoint, Serializable
{
    private static final long serialVersionUID = -7858869558953243875L;

    @Override
    // Send 401 to every unauthorised request
    public void commence(HttpServletRequest request, HttpServletResponse response,
                         AuthenticationException authException) throws IOException
    {
        response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Unauthorized");
    }
}