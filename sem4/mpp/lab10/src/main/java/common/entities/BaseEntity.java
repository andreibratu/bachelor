package common.entities;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;
import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.MappedSuperclass;
import java.io.Serializable;

@Data
@ToString
@MappedSuperclass
public abstract class BaseEntity<ID extends Serializable> implements Serializable
{
    @Id
    @GeneratedValue
    @JsonProperty("id")
    private ID id;
}
