package lab7.servlets;

import lombok.SneakyThrows;
import org.json.simple.JSONObject;
import lab7.servlets.helper.HttpHelper;
import lab7.services.AuthenticationService;
import org.springframework.beans.factory.annotation.Autowired;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.transaction.Transactional;

@WebServlet(
    name = "LoginServlet",
    urlPatterns = {"/login"}
)
public class LoginServlet extends HttpServlet
{
    private final AuthenticationService authenticationService;
    private final HttpHelper httpHelper;

    @Autowired
    public LoginServlet(AuthenticationService authenticationService, HttpHelper httpHelper)
    {
        this.authenticationService = authenticationService;
        this.httpHelper = httpHelper;
    }

    @SneakyThrows
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
    {
        JSONObject body = httpHelper.readBody(req);
        if (authenticationService.loginUser((String) body.get("username"), (String) body.get("password")))
        {
            String sessionToken = authenticationService.setUserSession((String) body.get("username"));
            Cookie sessionCookie = new Cookie("session", sessionToken);
            resp.addCookie(sessionCookie);
            sessionCookie.setMaxAge(7200);
            httpHelper.writeBody(resp, HttpServletResponse.SC_OK, "Ok");
        }
        else
        {
            httpHelper.writeBody(resp, HttpServletResponse.SC_BAD_REQUEST, "Bad credentials");
        }
    }
}
