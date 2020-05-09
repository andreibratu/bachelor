package lab7.servlets;

import lab7.entities.Post;
import lab7.entities.User;
import lab7.services.AuthenticationService;
import lab7.services.CommentsService;
import lab7.services.PostsService;
import lab7.servlets.helper.HttpHelper;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.List;
import java.util.Optional;

@WebServlet(
        name = "PostsServlet",
        urlPatterns = {"/posts"}
)
public class PostsServlet extends HttpServlet
{
    private final HttpHelper httpHelper;
    private final PostsService postsService;
    private final CommentsService commentsService;
    private final AuthenticationService authenticationService;

    @Autowired
    public PostsServlet(
            HttpHelper httpHelper,
            PostsService postsService,
            CommentsService commentsService,
            AuthenticationService authenticationService
    ) {
        this.authenticationService = authenticationService;
        this.postsService = postsService;
        this.httpHelper = httpHelper;
        this.commentsService = commentsService;
    }

    @Override
    @SuppressWarnings("unchecked")
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
    {
        Optional<User> authUser = authenticationService.validateRequest(req);
        authUser.ifPresentOrElse(
            (user) -> {
                JSONArray body = new JSONArray();
                List<Post> posts = postsService.getAllPosts();
                /*
                    Comments collection on Post is lazily loaded, thus Hibernate will do a separate query for them
                    whenever the field is accessed. This is exactly what happens when we try to JSON-ify the Post
                    entity. BUT, the field will be accessed outside the context manager that manages the Service
                    object method call, since the toJsonObject method is located on each instance i.e you are trying
                    to run a SQL query with the DB connection closed, majestically blowing in your face.
                    Setting comments by hand will set the field with objects that are actually loaded.

                    Bonus: @Transactional can only be placed on 'public' methods, so moving the CRUD in a Service
                    layer was necessary.

                    It's 01:39 as I'm writing this, please learn to respect the lazily loaded ones.
                 */
                posts.forEach(post -> post.setComments(commentsService.getCommentsForPost(post.getId())));
                posts.stream().map(Post::toJsonObject).forEach(body::add);
                httpHelper.writeBody(resp, HttpServletResponse.SC_OK, body.toJSONString());
            },
            () -> httpHelper.writeUnauthorizedResponse(resp)
        );
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
    {
        Optional<User> authUser = authenticationService.validateRequest(req);
        authUser.ifPresentOrElse(
            (user) -> {
                JSONObject body = httpHelper.readBody(req);
                Post newPost = postsService.createPost(user, (String) body.get("content"));
                httpHelper.writeBody(resp, HttpServletResponse.SC_CREATED, newPost.toJsonObject().toJSONString());
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
                try
                {
                    Integer id = Integer.parseInt(req.getParameter("id"));
                    if (postsService.deletePost(user, id))
                    {
                        httpHelper.writeBody(resp, HttpServletResponse.SC_OK, "Ok");
                    }
                    else
                    {
                        httpHelper.writeBody(resp, HttpServletResponse.SC_UNAUTHORIZED, "Entity not owned");
                    }
                }
                catch (RuntimeException e)
                {
                    httpHelper.writeBadRequestResponse(resp);
                }
            },
            () -> httpHelper.writeUnauthorizedResponse(resp)
        );
    }
}
