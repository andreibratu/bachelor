package lab7.servlets;

import lab7.entities.Comment;
import lab7.entities.User;
import lab7.services.AuthenticationService;
import lab7.services.CommentsService;
import lab7.servlets.helper.HttpHelper;
import org.json.simple.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.Optional;

@WebServlet(
        name = "CommentsServlet",
        urlPatterns = {"/comments"}
)
public class CommentsServlet extends HttpServlet
{
    private final HttpHelper httpHelper;
    private final CommentsService commentsService;
    private final AuthenticationService authenticationService;

    @Autowired
    public CommentsServlet(
            HttpHelper httpHelper,
            CommentsService commentsService,
            AuthenticationService authenticationService)
    {
        this.httpHelper = httpHelper;
        this.commentsService = commentsService;
        this.authenticationService = authenticationService;
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
    {
        Optional<User> authUser = authenticationService.validateRequest(req);
        authUser.ifPresentOrElse(
                (user) -> {
                    JSONObject body = httpHelper.readBody(req);
                    Integer post_id = ((Long) body.get("post_id")).intValue();
                    String content = (String) body.get("content");
                    Optional<Comment> newComment = commentsService.createComment(user, content, post_id);

                    if (newComment.isEmpty())
                    {
                        httpHelper.writeBadRequestResponse(resp);
                        return;
                    }

                    httpHelper.writeBody(
                            resp,
                            HttpServletResponse.SC_CREATED,
                            newComment.get().toJsonObject().toJSONString()
                    );
                },
                () -> httpHelper.writeUnauthorizedResponse(resp)
        );
    }

    @Override
    protected void doDelete(HttpServletRequest req, HttpServletResponse resp)
    {
        Optional<User> authUser = authenticationService.validateRequest(req);
        authUser.ifPresentOrElse(
            (user) -> {
                Integer id = Integer.parseInt(req.getParameter("id"));
                if (!commentsService.deleteComment(user, id))
                {
                    httpHelper.writeBadRequestResponse(resp);
                }
                else
                {
                    httpHelper.writeBody(resp, HttpServletResponse.SC_OK, "Ok");
                }
            },
            () -> httpHelper.writeUnauthorizedResponse(resp)
        );
    }
}
