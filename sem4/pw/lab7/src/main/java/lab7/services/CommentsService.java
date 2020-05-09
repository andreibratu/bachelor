package lab7.services;

import lab7.entities.Comment;
import lab7.entities.Post;
import lab7.entities.User;
import lab7.repositories.CommentRepository;
import lab7.repositories.PostRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.transaction.Transactional;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

@Service
@Transactional
public class CommentsService
{
    private final PostRepository postRepository;
    private final CommentRepository commentRepository;

    @Autowired
    public CommentsService(
        PostRepository postRepository,
        CommentRepository commentRepository
    ) {
        this.postRepository = postRepository;
        this.commentRepository = commentRepository;
    }

    public Set<Comment> getCommentsForPost(Integer post_id)
    {
        Set<Comment> comments = new HashSet<>();
        commentRepository.findCommentsByPostId(post_id).forEach(comments::add);
        return comments;
    }

    public Optional<Comment> createComment(User author, String content, Integer post_id)
    {
        Optional<Post> referredPost = postRepository.findById(post_id);

        if (referredPost.isEmpty()) return Optional.empty();

        Comment newComment = new Comment();
        newComment.setAuthor(author);
        newComment.setContent(content);
        newComment.setPost(referredPost.get());

        return Optional.of(commentRepository.save(newComment));
    }

    public boolean deleteComment(User requester, Integer comment_id)
    {
        if (!commentRepository
                .findById(comment_id).orElseThrow(RuntimeException::new)
                .getAuthor().getId().equals(requester.getId())
        )
        {
            return false;
        }
        else
        {
            commentRepository.deleteById(comment_id);
            return true;
        }
    }
}
