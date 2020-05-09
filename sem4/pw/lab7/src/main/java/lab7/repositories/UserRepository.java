package lab7.repositories;

import lab7.entities.User;
import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

import java.util.Optional;

@Repository
public interface UserRepository extends CrudRepository<User, Integer>
{
    User findByUsername(String username);

    Optional<User> findBySessionToken(String token);
}
