package common.entities;

import lombok.Data;
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
    private ID id;
}
