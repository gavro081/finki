package mk.ukim.finki.wp.lab.web.controller;

import jakarta.servlet.http.HttpServletRequest;
import jakarta.transaction.Transactional;
import mk.ukim.finki.wp.lab.model.Author;
import mk.ukim.finki.wp.lab.model.Book;
import mk.ukim.finki.wp.lab.service.AuthorService;
import mk.ukim.finki.wp.lab.service.BookService;
import mk.ukim.finki.wp.lab.service.impl.AuthorServiceImpl;
import mk.ukim.finki.wp.lab.service.impl.BookServiceImpl;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@Controller
@RequestMapping(value = {"/books", "/"})
public class BookController {
    private final BookService bookService;
    private final AuthorService authorService;

    public BookController(BookService bookService, AuthorService authorService) {
        this.bookService = bookService;
        this.authorService = authorService;
    }

    @GetMapping()
    public String getBooksPage(
            @RequestParam(required = false) String error,
            @RequestParam(required = false) Double matchedRating,
            @RequestParam(required = false) String matchedText,
            HttpServletRequest request,
            Model model){
        if (error != null && !error.isEmpty()){
            model.addAttribute("error", error);
        }
        model.addAttribute("user", request.getRemoteUser());
        List<Book> books =
                (matchedRating != null && matchedText != null)
                        ? bookService.searchBooks(matchedText, matchedRating)
                        : bookService.listAllSorted();
        model.addAttribute("books", books);
        return "listBooks";
    }

    @PostMapping("/add")
    @PreAuthorize("hasRole('ADMIN')")
    public String saveBook(@RequestParam String title,
                           @RequestParam String genre,
                           @RequestParam Double averageRating,
                           @RequestParam Long authorId){
        Author author = authorService.findByID(authorId);
        if (author == null) {
            return "redirect:/books?error=missingAuthor";
        }
        boolean add = bookService.addBook(title, genre, averageRating, author);
        if (!add){
            return "redirect:/books?error=invalidData";
        }
        return "redirect:/books";
    }

    @GetMapping("/book-form/{id}")
    @PreAuthorize("hasRole('ADMIN')")
    public String getEditBookForm(@PathVariable Long id, Model model){
        Book b = bookService.getById(id);
        if (b == null)
            return "redirect:/books?error=BookNotFound";
        Book book = bookService.getById(id);
        model.addAttribute("authors", authorService.findAll());
        model.addAttribute("book", book);
        return "book-form";
    }

    @PostMapping("/edit/{bookId}")
    @PreAuthorize("hasRole('ADMIN')")
    public String editBook(@PathVariable Long bookId,
                           @RequestParam String title,
                           @RequestParam String genre,
                           @RequestParam Double averageRating,
                           @RequestParam Long authorId){

        Author author = authorService.findByID(authorId);
        bookService.editBook(bookId, title, genre, averageRating, author);
        return "redirect:/books";
    }

    @GetMapping("/delete/{id}")
    @PreAuthorize("hasRole('ADMIN')")
    @Transactional
    public String deleteBook(@PathVariable Long id) {
        bookService.deleteBook(id);
        return "redirect:/books";
    }

    @GetMapping("/book-form")
    public String getAddBookPage(Model model){
        model.addAttribute("authors", authorService.findAll());
        return "book-form";
    }
}
