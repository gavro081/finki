package juni2023.z2_posts;

// printanjeto na tc 3 ne e u ist redosled ama ok e
import java.util.*;

class Post {
    private final String username;
    private final String postContent;
    private final Map<String, Comment> commentsMap;
    Post(String username, String postContent){
        this.username = username;
        this.postContent = postContent;
        this.commentsMap = new TreeMap<>();
    }

    void addComment (String username, String commentId, String content, String replyToId){
        Comment c = new Comment(username, content);
        commentsMap.put(commentId, c);
        if (replyToId != null){
            Comment comment = commentsMap.get(replyToId);
            if (comment != null){
                comment.addReply(c);
            }
        }
    }

    void likeComment(String commentId){
        commentsMap.get(commentId).likeComment();
    }

    @Override
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Post: ").append(this.postContent).append('\n');
        sb.append("Written by: ").append(this.username).append('\n');
        sb.append("Comments:\n");
        commentsMap.values().stream()
                .filter(c -> !c.hasParent())
                .sorted(Comparator.comparing(Comment::getLikesTotal).reversed()
//                        .thenComparing(Comment::getContent))
                )
                .forEach(c -> sb.append(c.print(1)));

        return sb.toString();
    }

}

class Comment {
    private final String username;
    private final String content;
    private boolean hasParentFlag = false;
    private int likes = 0;
    private final List<Comment> replies;

    public Comment(String username, String content) {
        this.username = username;
        this.content = content;
        this.replies = new ArrayList<>();
    }

    void addReply(Comment c){
        replies.add(c);
        c.setHasParentFlag();
    }

    void setHasParentFlag(){
        hasParentFlag = true;
    }

    public boolean hasParent(){
        return hasParentFlag;
    }

    void likeComment(){
        likes++;
    }

    public int getLikesTotal() {
        int count = likes;
        for (Comment c : replies){
            count += c.getLikesTotal();
        }
        return count;
    }

    public boolean hasReplies(){
        return !replies.isEmpty();
    }

    public String print(int depth){
        String indent = "    ".repeat(depth+1);
        StringBuilder sb = new StringBuilder();
        sb.append(indent).append("Comment: ").append(this.content).append("\n");
        sb.append(indent).append("Written by: ").append(this.username).append("\n");
        sb.append(indent).append("Likes: ").append(this.likes).append("\n");
        replies.sort(Comparator.comparing(Comment::getLikesTotal).reversed());
        for (Comment c : replies){
            sb.append(c.print(depth + 1));
        }
        return sb.toString();
    }

}

public class PostTester {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String postAuthor = sc.nextLine();
        String postContent = sc.nextLine();

        Post p = new Post(postAuthor, postContent);

        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            String[] parts = line.split(";");
            String testCase = parts[0];

            if (testCase.equals("addComment")) {
                String author = parts[1];
                String id = parts[2];
                String content = parts[3];
                String replyToId = null;
                if (parts.length == 5) {
                    replyToId = parts[4];
                }
                p.addComment(author, id, content, replyToId);
            } else if (testCase.equals("likes")) { //likes;1;2;3;4;1;1;1;1;1 example
                for (int i = 1; i < parts.length; i++) {
                    p.likeComment(parts[i]);
                }
            } else {
                System.out.println(p);
            }

        }
    }
}

