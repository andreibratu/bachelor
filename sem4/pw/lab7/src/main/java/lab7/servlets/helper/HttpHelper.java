package lab7.servlets.helper;

import lombok.SneakyThrows;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.springframework.stereotype.Component;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.Writer;
import java.util.stream.Collectors;

@Component
public class HttpHelper
{
    private final JSONParser jsonParser;

    public HttpHelper()
    {
        this.jsonParser = new JSONParser();
    }

    @SneakyThrows
    public JSONObject readBody(HttpServletRequest request)
    {
        String body = request.getReader().lines().collect(Collectors.joining());
        return (JSONObject) jsonParser.parse(body);
    }

    @SneakyThrows
    public void writeBody(HttpServletResponse response, int status, String body)
    {
        response.setContentType("application/json");
        response.setCharacterEncoding("UTF-8");
        response.setStatus(status);
        Writer writer = response.getWriter();
        writer.write(body);
        writer.flush();
    }

    public void writeUnauthorizedResponse(HttpServletResponse response)
    {
        writeBody(response, HttpServletResponse.SC_UNAUTHORIZED, "Authentication required");
    }

    public void writeBadRequestResponse(HttpServletResponse response)
    {
        writeBody(response, HttpServletResponse.SC_BAD_REQUEST, "Bad request");
    }
}
