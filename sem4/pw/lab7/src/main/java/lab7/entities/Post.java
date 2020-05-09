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
import java.util.HashSet;
import java.util.Set;
import java.util.stream.Collectors;

@Getter
@Setter
@Entity
@Table(name = "posts")
public class Post extends JsonEntity
{
    @Id
    @Column(name = "id", nullable = false)
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Integer id;

    @Column(name = "content", length = 1000)
    private String content;

    @CreationTimestamp
    private Timestamp createTimestamp;

    @UpdateTimestamp
    private Timestamp updateTimestamp;

    @ManyToOne
    private User author;

    @OneToMany(mappedBy = "post", cascade = CascadeType.ALL)
    private Set<Comment> comments;

    @PrePersist
    void onPersist()
    {
        this.comments = new HashSet<>();
    }

    @Override
    @SuppressWarnings("unchecked")
    public JSONObject toJsonObject()
    {
        JSONObject dto = new JSONObject();
        dto.put("post_id", id);
        dto.put("content", content);
        dto.put("create", createTimestamp.toString());
        dto.put("update", updateTimestamp.toString());
        dto.put("author", author.toJsonObject());
        /*

         */
        dto.put("comments", comments.stream().map(Comment::toJsonObject).collect(Collectors.toList()));
        return dto;
    }

}
