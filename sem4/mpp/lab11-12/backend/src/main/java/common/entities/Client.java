package common.entities;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.*;

import javax.persistence.Entity;
import java.io.Serializable;

@Data
@Entity
@ToString(callSuper = true)
@AllArgsConstructor
@NoArgsConstructor
@EqualsAndHashCode(callSuper = true)
public class Client extends BaseEntity<Long> implements Serializable
{
    @JsonProperty("name")
    private String name;

    @JsonProperty("address")
    private String address;
}
