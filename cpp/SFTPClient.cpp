#include <libssh/libssh.h>
#include <libssh/sftp.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>      // open() flags
#include <errno.h>
#include <string.h>

void download_file(const char *host, int port, const char *user, const char *password, const char *remote_path, const char *local_path) {
    ssh_session session = ssh_new();
    if (!session) {
        fprintf(stderr, "Error creando sesión SSH\n");
        return;
    }

    ssh_options_set(session, SSH_OPTIONS_HOST, host);
    ssh_options_set(session, SSH_OPTIONS_PORT, &port);
    ssh_options_set(session, SSH_OPTIONS_USER, user);

    if (ssh_connect(session) != SSH_OK) {
        fprintf(stderr, "Error conectando: %s\n", ssh_get_error(session));
        ssh_free(session);
        return;
    }

    if (ssh_userauth_password(session, NULL, password) != SSH_AUTH_SUCCESS) {
        fprintf(stderr, "Error de autenticación: %s\n", ssh_get_error(session));
        ssh_disconnect(session);
        ssh_free(session);
        return;
    }

    // Iniciar sesión SFTP
    sftp_session sftp = sftp_new(session);
    if (!sftp) {
        fprintf(stderr, "Error creando sesión SFTP: %s\n", ssh_get_error(session));
        ssh_disconnect(session);
        ssh_free(session);
        return;
    }

    if (sftp_init(sftp) != SSH_OK) {
        fprintf(stderr, "Error inicializando SFTP: %d\n", sftp_get_error(sftp));
        sftp_free(sftp);
        ssh_disconnect(session);
        ssh_free(session);
        return;
    }

    // Abrir archivo remoto
    sftp_file remote_file = sftp_open(sftp, remote_path, O_RDONLY, 0);
    if (!remote_file) {
        fprintf(stderr, "Error abriendo archivo remoto: %s\n", ssh_get_error(session));
        sftp_free(sftp);
        ssh_disconnect(session);
        ssh_free(session);
        return;
    }

    FILE *local_file = fopen(local_path, "wb");
    if (!local_file) {
        fprintf(stderr, "Error creando archivo local: %s\n", strerror(errno));
        sftp_close(remote_file);
        sftp_free(sftp);
        ssh_disconnect(session);
        ssh_free(session);
        return;
    }

    char buffer[1024];
    int nbytes;
    while ((nbytes = sftp_read(remote_file, buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, 1, nbytes, local_file);
    }

    if (nbytes < 0) {
        fprintf(stderr, "Error leyendo archivo remoto: %s\n", ssh_get_error(session));
    }

    fclose(local_file);
    sftp_close(remote_file);
    sftp_free(sftp);
    ssh_disconnect(session);
    ssh_free(session);

    printf("Archivo descargado correctamente a %s\n", local_path);
}

int main() {
    const char *host = "4.tcp.ngrok.io";
    int port = 14835;
    const char *user = "LORENZO.RAMIREZC";
    const char *password = "20550074";

    const char *remote_path = "/home/LORENZO.RAMIREZC/workspace/Admission_Predict.csv";
    const char *local_path = "Admission_Predict.csv";

    download_file(host, port, user, password, remote_path, local_path);

    return 0;
}
