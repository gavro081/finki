package k2.z33_TaskManager;


import java.io.*;
import java.time.Duration;
import java.time.LocalDateTime;
import java.util.*;

class DeadlineNotValidException extends Exception {
    DeadlineNotValidException(LocalDateTime deadline) {
        super("The deadline " + deadline + " has already passed");
    }
}

interface ITask {
    int getPriority();

    LocalDateTime getDeadline();

    String getCategory();

    String getName();

    String getDesc();
}

class Task implements ITask {
    private final String name;
    private final String category;
    private final String description;

    public Task(String category, String name, String description) {
        this.category = category;
        this.name = name;
        this.description = description;
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public String getCategory() {
        return category;
    }

    @Override
    public String getDesc() {
        return description;
    }

    @Override
    public int getPriority() {
        return Integer.MAX_VALUE;
    }

    @Override
    public LocalDateTime getDeadline() {
        return LocalDateTime.MAX;
    }

    @Override
    public String toString() {
        return "Task{" +
                "name='" + name + '\'' +
                ", description='" + description + '\'' +
                '}';
    }
}

abstract class TaskDecorator implements ITask {
    ITask decoratedTask;

    public TaskDecorator(ITask decoratedTask) {
        this.decoratedTask = decoratedTask;
    }
}

class PriorityDecorator extends TaskDecorator {
    private final int priority;

    public PriorityDecorator(ITask decoratedTask, int priority) {
        super(decoratedTask);
        this.priority = priority;
    }

    @Override
    public String getCategory() {
        return this.decoratedTask.getCategory();
    }

    @Override
    public String getName() {
        return this.decoratedTask.getName();
    }

    @Override
    public String getDesc() {
        return this.decoratedTask.getCategory();
    }

    public int getPriority() {
        return priority;
    }

    @Override
    public LocalDateTime getDeadline() {
        return this.decoratedTask.getDeadline();
    }

    @Override
    public String toString() {
        return decoratedTask
                .toString()
                .replace("}", "") +
                ", priority=" + priority + "}";
    }
}

class DueDateDecorator extends TaskDecorator {
    private final LocalDateTime deadline;

    public DueDateDecorator(ITask decoratedTask, LocalDateTime dueDate) throws DeadlineNotValidException {
        super(decoratedTask);
        if (dueDate.isBefore(LocalDateTime.of(2020, 6, 2, 0, 0))) {
            throw new DeadlineNotValidException(dueDate);
        }
        this.deadline = dueDate;
    }

    public LocalDateTime getDeadline() {
        return deadline;
    }

    @Override
    public String getCategory() {
        return this.decoratedTask.getCategory();
    }

    @Override
    public String getName() {
        return this.decoratedTask.getName();
    }

    @Override
    public String getDesc() {
        return this.decoratedTask.getDesc();
    }

    @Override
    public int getPriority() {
        return this.decoratedTask.getPriority();
    }

    @Override
    public String toString() {
        return decoratedTask
                .toString()
                .replace("}", "") +
                ", deadline=" + deadline + "}";
    }
}

class TaskFactory {
    public static ITask createTask(String line) {
        String[] parts = line.split(",");
        ITask t = new Task(parts[0], parts[1], parts[2]);
        if (parts.length >= 4) {
            if (parts[3].contains(":")) {
                try {
                    t = new DueDateDecorator(t, LocalDateTime.parse(parts[3]));
                } catch (DeadlineNotValidException e) {
                    System.out.println(e.getMessage());
                    return null;
                }
                if (parts.length >= 5) {
                    return new PriorityDecorator(t, Integer.parseInt(parts[4]));
                }
            } else {
                return new PriorityDecorator(t, Integer.parseInt(parts[3]));
            }
        }
        return t;
    }
}

class TaskManager {
    private final Map<String, List<ITask>> tasks;

    public TaskManager() {
        this.tasks = new TreeMap<>();
    }

    void readTasks(InputStream inputStream) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(inputStream));
        String line;
        while ((line = br.readLine()) != null && !line.isEmpty()) {
            ITask t = TaskFactory.createTask(line);
            if (t == null) continue;
            tasks.computeIfAbsent(t.getCategory(), x -> new ArrayList<>()).add(t);

            // posigurna opcija
//            tasks.putIfAbsent(t.getCategory(), new ArrayList<>());
//            tasks.get(t.getCategory()).add(t);
        }

    }

    void printTasks(OutputStream os, boolean includePriority, boolean includeCategory) {
        PrintWriter pw = new PrintWriter(os);
        LocalDateTime now = LocalDateTime.now();

        Comparator<ITask> deadlineComparator = Comparator.comparing(task -> Duration.between(now, task.getDeadline()));
        Comparator<ITask> priorityComparator = Comparator.comparing(ITask::getPriority).thenComparing(deadlineComparator);

        Comparator<ITask> activeComparator = includePriority ? priorityComparator : deadlineComparator;

        if (includeCategory) {
            tasks.forEach((category, tasks_) -> {
                pw.println(category.toUpperCase());
                tasks_.stream()
                        .sorted(activeComparator)
                        .forEach(pw::println);
            });
        } else {
            tasks.values().stream()
                    .flatMap(List::stream)
                    .sorted(activeComparator)
                    .forEach(pw::println);
        }

        pw.flush();
    }
}

public class TasksManagerTest {

    public static void main(String[] args) throws Exception {

        TaskManager manager = new TaskManager();

        System.out.println("Tasks reading");
        manager.readTasks(System.in);
        System.out.println("By categories with priority");
        manager.printTasks(System.out, true, true);
        System.out.println("-------------------------");
        System.out.println("By categories without priority");
        manager.printTasks(System.out, false, true);
        System.out.println("-------------------------");
        System.out.println("All tasks without priority");
        manager.printTasks(System.out, false, false);
        System.out.println("-------------------------");
        System.out.println("All tasks with priority");
        manager.printTasks(System.out, true, false);
        System.out.println("-------------------------");

    }
}

