import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;
/**
 * The very basic socket server that only listen one single message.
 */

public class BaseSocketServer {

    private ServerSocket server;
    private Socket socket;
    private int port;
    private InputStream inputStream;
    private static final int MAX_BUFFER_SIZE = 1024;

    public int getPort() {
        return port;
    }

    public void setPort(int port) {
        this.port = port;
    }

    public BaseSocketServer(int port) {
        this.port = port;
    }

    public void runServerSingle() throws IOException {
        this.server = new ServerSocket(this.port);

        System.out.println("base socket server started.");
        // the code will block here till the request come.
        this.socket = server.accept();

        this.inputStream = this.socket.getInputStream();

        byte[] readBytes = new byte[MAX_BUFFER_SIZE];

        int msgLen;
        StringBuilder stringBuilder = new StringBuilder();

        while ((msgLen = inputStream.read(readBytes)) != -1) {
            stringBuilder.append(new String(readBytes,0,msgLen,"UTF-8"));
        }

        System.out.println("get message from client: " + stringBuilder);

        inputStream.close();
        socket.close();
        server.close();
    }
	public void runServer() throws IOException {
        this.server = new ServerSocket(this.port);

        System.out.println("base socket server started.");

        this.socket = server.accept();
        // the code will block here till the request come.

        this.inputStream = this.socket.getInputStream();
        Scanner sc = new Scanner(this.inputStream);
        while (sc.hasNextLine()) {
            System.out.println("get info from client: " + sc.nextLine());
        } // 循环接收并输出消息内容
        this.inputStream.close();
        socket.close();
    }

    public static void main(String[] args) {
        BaseSocketServer bs = new BaseSocketServer(9799);
        try {
			bs.runServer();
            //bs.runServerSingle();
        }catch (IOException e) {
            e.printStackTrace();
        }

    }
}
