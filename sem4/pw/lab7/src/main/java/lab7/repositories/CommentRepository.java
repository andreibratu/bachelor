package lab7.repositories;

import lab7.entities.Comment;
import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface CommentRepository extends CrudRepository<Comment, Integer>
{
    Iterable<Comment> findCommentsByPostId(Integer post_id);
}
