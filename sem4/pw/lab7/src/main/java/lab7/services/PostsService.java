package lab7.services;

import lab7.entities.Post;
import lab7.entities.User;
import lab7.repositories.PostRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.transaction.Transactional;
import java.util.Comparator;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

@Service
@Transactional
public class PostsService
{
    private final PostRepository postRepository;

    @Autowired
    public PostsService(PostRepository postRepository)
    {
        this.postRepository = postRepository;
    }

    public List<Post> getAllPosts()
    {
        Comparator<Post> comp = Comparator
                .comparingInt((Post p) -> p.getCreateTimestamp().getNanos())
                .reversed();
        return StreamSupport.stream(postRepository.findAll().spliterator(), false)
                .sorted(comp)
                .collect(Collectors.toList());
    }

    public Post createPost(User author, String content)
    {
        Post newPost = new Post();
        newPost.setContent(content);
        newPost.setAuthor(author);
        return postRepository.save(newPost);
    }

    public boolean deletePost(User requester, Integer post_id)
    {
        Optional<Post> post = postRepository.findById(post_id);
        if (post.isEmpty() ||
            !post.get().getAuthor().getId().equals(requester.getId())
        )
        {
            return false;
        }
        postRepository.deleteById(post_id);
        return true;
    }
}
