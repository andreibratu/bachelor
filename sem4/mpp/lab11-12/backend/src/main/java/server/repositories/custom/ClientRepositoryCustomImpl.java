package server.repositories.custom;

import org.hibernate.Criteria;
import org.hibernate.Session;
import org.springframework.stereotype.Component;
import server.entities.Client;
import server.entities.Client_;
import server.entities.Rental;
import server.entities.Rental_;
import server.repositories.base.CustomRepositorySupport;

import javax.persistence.EntityManager;
import javax.persistence.Query;
import javax.persistence.criteria.*;
import java.util.List;

@Component
@SuppressWarnings({"unchecked", "deprecation", "error"})
public class ClientRepositoryCustomImpl extends CustomRepositorySupport implements ClientRepositoryCustom
{
    @Override
    public List<Client> findAllWithRentalsAndMovieJPQL()
    {
        EntityManager entityManager = getEntityManager();
        Query query = entityManager.createQuery("select distinct c from Client c");

        return (List<Client>) query.getResultList();
    }

    @Override
    public List<Client> findAllWithRentalsAndMovieCriteriaAPI()
    {
        EntityManager entityManager = getEntityManager();

        CriteriaBuilder criteriaBuilder = entityManager.getCriteriaBuilder();
        CriteriaQuery<Client> query = criteriaBuilder.createQuery(Client.class);
        query.distinct(Boolean.TRUE);
        Root<Client> root = query.from(Client.class);
        query.select(root);
        Fetch<Client, Rental> clientsWithRentalsFetch = root.fetch(Client_.rentals, JoinType.LEFT);
        clientsWithRentalsFetch.fetch(Rental_.movie, JoinType.LEFT);

        return entityManager.createQuery(query).getResultList();
    }

    @Override
    public List<Client> findAllWithRentalsAndMovieSQL()
    {
        Session session = getEntityManager().unwrap(Session.class);

        org.hibernate.query.Query<?> query = session.createSQLQuery("select distinct {c.*}, {r.*}, {m.*} " +
                "from Client c " +
                "left join Rental r on c.id=r.client_id " +
                "left join Movie m on r.movie_id=m.id")
                .addEntity("c", Client.class)
                .addJoin("r", "c.rentals")
                .addJoin("m", "r.movie")
                // Hibernate deprecated this without implementing an alternative LMAO
                .setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);

        return (List<Client>) query.getResultList();
    }

    @Override
    public List<Client> findAllWithRentalsSortedJPQL()
    {
        EntityManager entityManager = getEntityManager();
        Query query = entityManager.createQuery(
                "select distinct c from Client c order by c.name");
        return (List<Client>) query.getResultList();
    }

    @Override
    public List<Client> findAllWithRentalsSortedCriteriaAPI()
    {
        EntityManager entityManager = getEntityManager();

        CriteriaBuilder criteriaBuilder = entityManager.getCriteriaBuilder();
        CriteriaQuery<Client> query = criteriaBuilder.createQuery(Client.class);
        query.distinct(Boolean.TRUE);
        Root<Client> root = query.from(Client.class);
        query.orderBy(criteriaBuilder.asc(root.get(Client_.name)));
        query.select(root);
        Fetch<Client, Rental> bookPurchaseFetch = root.fetch(Client_.rentals, JoinType.LEFT);
        bookPurchaseFetch.fetch(Rental_.movie, JoinType.LEFT);

        return entityManager.createQuery(query).getResultList();
    }

    @Override
    public List<Client> findAllWithRentalsSortedSQL()
    {
        Session session = getEntityManager().unwrap(Session.class);

        org.hibernate.query.Query<?> query = session.createSQLQuery(
                "select distinct {c.*}, {r.*}, {m.*} " +
                "from Client c " +
                "left join Rental r on c.id=r.client_id " +
                "left join Movie m on r.movie_id=m.id " +
                "order by c.name")
                .addEntity("c", Client.class)
                .addJoin("r", "c.rentals")
                .addJoin("m", "r.movie")
                // Hibernate deprecated this without implementing an alternative LMAO
                .setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);


        return (List<Client>) query.getResultList();
    }
}
