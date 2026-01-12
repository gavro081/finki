package mk.ukim.finki.wp.kol2025g3.service.impl;

import lombok.AllArgsConstructor;
import mk.ukim.finki.wp.kol2025g3.model.Expense;
import mk.ukim.finki.wp.kol2025g3.model.ExpenseCategory;
import mk.ukim.finki.wp.kol2025g3.repository.ExpenseRepository;
import mk.ukim.finki.wp.kol2025g3.service.ExpenseService;
import mk.ukim.finki.wp.kol2025g3.service.VendorService;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.jpa.domain.Specification;
import org.springframework.stereotype.Service;

import java.time.LocalDate;
import java.util.List;

import static mk.ukim.finki.wp.kol2025g3.service.FieldFilterSpecification.*;

@Service
@AllArgsConstructor
public class ExpenseServiceImpl implements ExpenseService {
    private final ExpenseRepository repository;
    private final VendorService vendorService;
    @Override
    public List<Expense> listAll() {
        return repository.findAll();
    }

    @Override
    public Expense findById(Long id) {
        return repository.findById(id).get();
    }

    @Override
    public Expense create(String title, LocalDate dateCreated, Double amount, Integer daysToExpire, ExpenseCategory expenseCategory, Long vendorId) {
        return repository.save(new Expense(title, dateCreated, amount, daysToExpire, expenseCategory, vendorService.findById(vendorId)));
    }

    @Override
    public Expense update(Long id, String title, LocalDate dateCreated, Double amount, Integer daysToExpire, ExpenseCategory expenseCategory, Long vendorId) {
        Expense e = findById(id);
        e.setTitle(title);
        e.setDateCreated(dateCreated);
        e.setAmount(amount);
        e.setDaysToExpire(daysToExpire);
        e.setExpenseCategory(expenseCategory);
        e.setVendor(vendorService.findById(vendorId));
        repository.save(e);
        return e;
    }

    @Override
    public Expense delete(Long id) {
        Expense e = findById(id);
        repository.delete(e);
        return e;
    }

    @Override
    public Expense extendExpiration(Long id) {
        Expense e = findById(id);
        System.out.println("ok");
        e.setDaysToExpire(e.getDaysToExpire() + 1);
        repository.save(e);
        return e;
    }

    @Override
    public Page<Expense> findPage(String title, ExpenseCategory expenseCategory, Long vendor, int pageNum, int pageSize) {
        Specification<Expense> specification = Specification.allOf(
                filterContainsText(Expense.class, "title", title),
                filterEqualsV(Expense.class, "expenseCategory", expenseCategory),
                filterEquals(Expense.class, "vendor.id", vendor)
        );

        return this.repository.findAll(
                specification,
                PageRequest.of(pageNum, pageSize)
        );
    }
}
