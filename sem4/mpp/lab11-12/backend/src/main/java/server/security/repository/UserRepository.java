package server.security.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import server.security.model.User;

@Repository
public interface UserRepository extends JpaRepository<User, Long>
{
    User findUserByUsername(String username);
}
