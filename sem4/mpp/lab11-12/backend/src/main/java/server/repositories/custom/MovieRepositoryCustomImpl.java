package server.repositories.custom;

import org.hibernate.Criteria;
import org.hibernate.Session;
import org.springframework.stereotype.Component;
import server.entities.*;
import server.repositories.base.CustomRepositorySupport;

import javax.persistence.EntityManager;
import javax.persistence.Query;
import javax.persistence.criteria.*;
import java.util.List;

@Component
@SuppressWarnings({"unchecked", "deprecation"})
public class MovieRepositoryCustomImpl extends CustomRepositorySupport implements MovieRepositoryCustom
{
    @Override
    public List<Movie> findAllWithRentalsAndClientJPQL()
    {
        EntityManager entityManager = getEntityManager();
        Query query = entityManager.createQuery("select distinct m from Movie m");

        return (List<Movie>) query.getResultList();
    }

    @Override
    public List<Movie> findAllWithRentalsAndClientCriteriaAPI()
    {
        EntityManager entityManager = getEntityManager();

        CriteriaBuilder criteriaBuilder = entityManager.getCriteriaBuilder();
        CriteriaQuery<Movie> query = criteriaBuilder.createQuery(Movie.class);
        query.distinct(Boolean.TRUE);
        Root<Movie> root = query.from(Movie.class);
        query.select(root);
        Fetch<Movie, Rental> clientsWithRentalsFetch = root.fetch(Movie_.rentals, JoinType.LEFT);
        clientsWithRentalsFetch.fetch(Rental_.client, JoinType.LEFT);

        return entityManager.createQuery(query).getResultList();
    }

    @Override
    public List<Movie> findAllWithRentalsAndClientSQL()
    {
        Session session = getEntityManager().unwrap(Session.class);

        org.hibernate.query.Query<?> query = session.createSQLQuery("select distinct {m.*}, {r.*}, {c.*} " +
                "from Movie m " +
                "left join Rental r on m.id=r.movie_id " +
                "left join Client c on r.client_id=c.id")
                .addEntity("m", Movie.class)
                .addJoin("r", "m.rentals")
                .addJoin("c", "r.client")
                .addEntity("m", Movie.class)
                // Hibernate deprecated this without implementing an alternative LMAO
                .setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);

        return (List<Movie>) query.getResultList();
    }

    @Override
    public List<Movie> findAllWithRentalsSortedJPQL()
    {
        EntityManager entityManager = getEntityManager();
        Query query = entityManager.createQuery(
                "select distinct m from Movie m order by m.title");
        return (List<Movie>) query.getResultList();
    }

    @Override
    public List<Movie> findAllWithRentalsSortedCriteriaAPI()
    {
        EntityManager entityManager = getEntityManager();

        CriteriaBuilder criteriaBuilder = entityManager.getCriteriaBuilder();
        CriteriaQuery<Movie> query = criteriaBuilder.createQuery(Movie.class);
        query.distinct(Boolean.TRUE);
        Root<Movie> root = query.from(Movie.class);
        query.orderBy(criteriaBuilder.asc(root.get(Movie_.title)));
        query.select(root);
        Fetch<Movie, Rental> clientsWithRentalsFetch = root.fetch(Movie_.rentals, JoinType.LEFT);
        clientsWithRentalsFetch.fetch(Rental_.client, JoinType.LEFT);

        return entityManager.createQuery(query).getResultList();
    }

    @Override
    public List<Movie> findAllWithRentalsSortedSQL()
    {
        Session session = getEntityManager().unwrap(Session.class);

        org.hibernate.query.Query<?> query = session.createSQLQuery("select distinct {m.*}, {r.*}, {c.*} " +
                "from Movie m " +
                "left join Rental r on m.id=r.movie_id " +
                "left join Client c on r.client_id=c.id " +
                "order by m.title")
                .addEntity("m", Movie.class)
                .addJoin("r", "m.rentals")
                .addJoin("c", "r.client")
                .addEntity("m", Movie.class)
                // Hibernate deprecated this without implementing an alternative LMAO
                .setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);

        return (List<Movie>) query.getResultList();
    }
}
