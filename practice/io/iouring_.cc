#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <liburing.h>

#define QUEUE_DEPTH 32  // Number of entries in the submission/completion queues
#define BLOCK_SIZE 4096 // Size of each read operation

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct io_uring ring;
    if (io_uring_queue_init(QUEUE_DEPTH, &ring, 0) < 0) { // Initialize io_uring
        perror("io_uring_queue_init");
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    char buffer[BLOCK_SIZE]; // Buffer to store read data

    // Prepare and submit read request
    struct io_uring_sqe *sqe = io_uring_get_sqe(&ring);
    io_uring_prep_read(sqe, fd, buffer, BLOCK_SIZE, 0); // Read from offset 0
    io_uring_submit(&ring);

    struct io_uring_cqe *cqe;
    
    while (1) { // Event loop to handle completions
        int ret = io_uring_wait_cqe(&ring, &cqe); // Wait for completion
        if (ret < 0) {
            perror("io_uring_wait_cqe");
            break; 
        }

        if (cqe->res <= 0) { // End of file or error
            if (cqe->res == 0) {
                printf("End of file\n");
            } else {
                fprintf(stderr, "Read error: %s\n", strerror(-cqe->res));
            }
            break;
        }

        // Process the read data (cqe->res contains number of bytes read)
        write(STDOUT_FILENO, buffer, cqe->res); // Write to standard output

        // Prepare the next read request (adjust the offset)
        off_t next_offset = cqe->res + cqe->off;
        io_uring_prep_read(sqe, fd, buffer, BLOCK_SIZE, next_offset);
        io_uring_submit(&ring);

        io_uring_cqe_seen(&ring, cqe); // Mark CQE as seen
    }

    close(fd);
    io_uring_queue_exit(&ring); // Clean up
    return 0;
}
