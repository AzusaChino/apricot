package main

import (
	"fmt"
	"net"
	"time"
)

func main() {
	msg := fmt.Sprintf("test")
	msgPrefix := "some-prefix"
	c, _ := net.Dial("tcp", "127.0.0.1:12345")
	defer c.Close()

	for i := 0; i < 10; i++ {
		c.Write([]byte(fmt.Sprintf("%s%s", msgPrefix, msg)))
		time.Sleep(time.Millisecond * time.Duration(100))
	}

	c.Write([]byte("this won't be parsed"))
}
