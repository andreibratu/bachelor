package common.entities;

import javax.persistence.Entity;
import java.io.Serializable;

@Entity
public class Client extends BaseEntity<Long> implements Serializable
{
    private String name;

    private String address;

    public Client() { }

    public Client(String name, String address)
    {
        this.name = name.trim();
        this.address = address.trim();
    }

    public Client(Long id, String name, String address)
    {
        this.setId(id);
        this.name = name;
        this.address = address;
    }

    public String getName()
    {
        return name;
    }

    public void setName(String name)
    {
        this.name = name;
    }

    public String getAddress()
    {
        return address;
    }

    public void setAddress(String address)
    {
        this.address = address;
    }

    @Override
    public boolean equals(Object o)
    {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Client client = (Client) o;

        if (!address.equals(client.address)) return false;
        return name.equals(client.name);

    }

    @Override
    public String toString()
    {
        return "Client{" +
                "name= '" + name + '\'' +
                ", address= '" + address + '\'' +
                "} " + super.toString();
    }
}
