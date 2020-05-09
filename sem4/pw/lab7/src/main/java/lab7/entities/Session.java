package lab7.entities;

import lombok.Getter;
import lombok.Setter;
import org.apache.commons.lang.time.DateUtils;

import javax.persistence.*;
import java.util.Date;

@Getter
@Setter
@Entity
@Table(name = "sessions")
public class Session
{
    @Id
    @Column(nullable = false)
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Integer id;

    @Column(nullable = false)
    private String token;

    @OneToOne(mappedBy = "session")
    private User user;

    @Column(nullable = false)
    private Date ttl;

    @PrePersist
    public void onPersist()
    {
        Date now = new Date();
        this.ttl = DateUtils.addHours(now, 2);
    }

    @PreUpdate
    public void onUpdate()
    {
        Date now = new Date();
        this.ttl = DateUtils.addHours(now, 2);
    }
}
