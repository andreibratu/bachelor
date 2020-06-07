package server.services.entity;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;
import server.entities.Client;
import server.repositories.ClientRepository;
import server.services.base.EntityService;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Optional;

@Component
@SuppressWarnings("unchecked")
public class ClientEntityServiceImplementation implements EntityService<Client>
{
    private final ClientRepository clientRepository;

    @Value("${repository.client.getAll}")
    private String getAllMethodName;

    @Value("${repository.client.getAllSorted}")
    private String getAllSortedMethodName;

    @Autowired
    public ClientEntityServiceImplementation(ClientRepository clientRepository)
    {
        this.clientRepository = clientRepository;
    }

    @Override
    public Client addEntity(Client entity)
    {
        if (entity == null) throw new IllegalArgumentException();
        return this.clientRepository.save(entity);
    }

    @Override
    public Iterable<Client> getAllEntities(int page)
    {
        System.out.println(getAllMethodName);
        try
        {
            Method getAllMethod = ClientRepository.class.getMethod(getAllMethodName);
            return (Iterable<Client>) getAllMethod.invoke(this.clientRepository);
        } catch (NoSuchMethodException |
                IllegalAccessException |
                InvocationTargetException e)
        {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public Iterable<Client> getAllEntitiesSorted(int page)
    {
        try
        {
            Method getAllMethod = ClientRepository.class.getMethod(getAllSortedMethodName);
            return (Iterable<Client>) getAllMethod.invoke(this.clientRepository);
        }
        catch (NoSuchMethodException |
                IllegalAccessException |
                InvocationTargetException e)
        {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public Optional<Client> deleteEntity(Long id)
    {
        Optional<Client> found = clientRepository.findById(id);
        clientRepository.deleteById(id);
        return found;
    }

    @Override
    public Optional<Client> updateEntity(Client updatedEntity)
    {
        Optional<Client> old = clientRepository.findById(updatedEntity.getId());
        clientRepository.deleteById(updatedEntity.getId());
        clientRepository.save(updatedEntity);
        return old;
    }

    @Override
    public Optional<Client> getEntity(Long id)
    {
        return clientRepository.findById(id);
    }
}
