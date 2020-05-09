package lab7.servlets;

import lab7.entities.User;
import lab7.servlets.helper.HttpHelper;
import lab7.services.AuthenticationService;
import org.springframework.beans.factory.annotation.Autowired;

import java.util.Optional;
import javax.servlet.http.HttpServlet;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(
    name = "UsersServlet",
    urlPatterns = {"/users"}
)
public class UsersServlet extends HttpServlet
{
    private final HttpHelper httpHelper;
    private final AuthenticationService authenticationService;

    @Autowired
    public UsersServlet(AuthenticationService authenticationService, HttpHelper httpHelper)
    {
        this.httpHelper = httpHelper;
        this.authenticationService = authenticationService;
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
    {
        Optional<User> authUser = authenticationService.validateRequest(req);
        authUser.ifPresentOrElse(
            (user) -> httpHelper.writeBody(resp, HttpServletResponse.SC_OK, user.toJsonObject().toJSONString()),
            () -> httpHelper.writeUnauthorizedResponse(resp)
        );
    }
}
