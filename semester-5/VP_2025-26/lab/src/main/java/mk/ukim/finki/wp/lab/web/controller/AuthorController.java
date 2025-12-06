package mk.ukim.finki.wp.lab.web.controller;

import mk.ukim.finki.wp.lab.service.AuthorService;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@RequestMapping("/authors")
public class AuthorController {
    private final AuthorService authorService;

    public AuthorController(AuthorService authorService) {
        this.authorService = authorService;
    }

    @GetMapping
    public String showAuthors(Model model){
        model.addAttribute("authors", authorService.findAll());
        return "listAuthors";
    }

    @GetMapping("/like/{id}")
    public String likeAuthor(@PathVariable Long id){
        authorService.incrementLikesByAuthor(id);
        return "redirect:/authors";
    }
}
