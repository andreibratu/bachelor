package lab7.entities;

import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.Getter;
import lombok.Setter;
import org.hibernate.annotations.CreationTimestamp;
import org.hibernate.annotations.UpdateTimestamp;
import org.json.simple.JSONObject;

import javax.persistence.*;
import java.sql.Timestamp;

@Getter
@Setter
@Entity
@Table(name = "comments")
public class Comment extends JsonEntity
{
    @Id
    @Column(name = "id", nullable = false)
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Integer id;

    @Column(name = "content", nullable = false, length = 300)
    private String content;

    @CreationTimestamp
    private Timestamp createTimestamp;

    @UpdateTimestamp
    private Timestamp updateTimestamp;

    @ManyToOne
    private Post post;

    @ManyToOne()
    private User author;

    @Override
    @SuppressWarnings("unchecked")
    public JSONObject toJsonObject()
    {
        JSONObject dto = new JSONObject();
        dto.put("comment_id", id);
        dto.put("content", content);
        dto.put("create", createTimestamp.toString());
        dto.put("update", updateTimestamp.toString());
        dto.put("author", author.toJsonObject());
        return dto;
    }
}
