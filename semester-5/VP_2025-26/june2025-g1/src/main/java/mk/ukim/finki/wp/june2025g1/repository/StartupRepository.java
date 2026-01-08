package mk.ukim.finki.wp.june2025g1.repository;

import mk.ukim.finki.wp.june2025g1.model.Startup;
import org.springframework.stereotype.Repository;

@Repository
public interface StartupRepository extends JpaSpecificationRepository<Startup, Long> {
}
