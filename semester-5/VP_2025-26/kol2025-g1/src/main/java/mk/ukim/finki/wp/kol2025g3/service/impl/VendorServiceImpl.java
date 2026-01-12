package mk.ukim.finki.wp.kol2025g3.service.impl;

import lombok.AllArgsConstructor;
import mk.ukim.finki.wp.kol2025g3.model.Vendor;
import mk.ukim.finki.wp.kol2025g3.repository.VendorRepository;
import mk.ukim.finki.wp.kol2025g3.service.VendorService;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
@AllArgsConstructor
public class VendorServiceImpl implements VendorService {
    private final VendorRepository repository;

    @Override
    public Vendor findById(Long id) {
        return repository.findById(id).get();
    }

    @Override
    public List<Vendor> listAll() {
        return repository.findAll();
    }

    @Override
    public Vendor create(String name) {
        return repository.save(new Vendor(name));
    }
}
