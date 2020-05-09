package lab7.servlets;

import lab7.entities.User;
import lab7.servlets.helper.HttpHelper;
import lab7.services.AuthenticationService;
import org.springframework.beans.factory.annotation.Autowired;

import java.util.Optional;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.transaction.Transactional;

@WebServlet(
        name = "LogoutServlet",
        urlPatterns = {"/logout"}
)
public class LogoutServlet extends HttpServlet
{
    private final AuthenticationService authenticationService;
    private final HttpHelper httpHelper;

    @Autowired
    public LogoutServlet(AuthenticationService authenticationService, HttpHelper httpHelper)
    {
        this.authenticationService = authenticationService;
        this.httpHelper = httpHelper;
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
    {
        Optional<User> authUser = authenticationService.validateRequest(req);
        authUser.ifPresentOrElse(
                (user) -> {
                    Cookie sessionFinished = new Cookie("session", "");
                    sessionFinished.setMaxAge(0);
                    resp.addCookie(sessionFinished);
                    resp.setStatus(HttpServletResponse.SC_OK);
                },
                () -> httpHelper.writeUnauthorizedResponse(resp)
        );
    }
}

