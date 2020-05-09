package lab7.entities;

import lombok.Getter;
import lombok.Setter;
import org.json.simple.JSONObject;

import javax.persistence.*;
import java.util.HashSet;
import java.util.Set;

@Getter
@Setter
@Entity
@Table(name = "users")
public class User extends JsonEntity
{
    @Id
    @Column(name = "id")
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Integer id;

    @Column(name = "username")
    private String username;

    @Column(name = "password_hash")
    private String passwordHash;

    @OneToMany(mappedBy = "author", cascade = CascadeType.ALL)
    private Set<Post> posts;

    @OneToMany(mappedBy = "author", cascade = CascadeType.ALL)
    private Set<Comment> comments;

    @OneToOne(cascade = CascadeType.ALL)
    private Session session;

    @PrePersist
    void onPersist()
    {
        this.posts = new HashSet<>();
        this.comments = new HashSet<>();
    }

    @Override
    @SuppressWarnings("unchecked")
    public JSONObject toJsonObject()
    {
        JSONObject dto = new JSONObject();
        dto.put("user_id", id);
        dto.put("username", username);
        return dto;
    }
}
