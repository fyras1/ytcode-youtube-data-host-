#include <gtk/gtk.h>
#include <iostream>
#include <string>
#include <encode.hpp>

// Button click callbacks
void on_decode_button_clicked(GtkWidget* widget, gpointer data) {
    GtkEntry* entry = GTK_ENTRY(data);
    const char* text = gtk_entry_get_text(entry);
    if (text && *text) {
        std::cout << "Decoding link: " << text << std::endl;
    } else {
        std::cout << "No link entered!" << std::endl;
    }
}

void on_file_button_clicked(GtkWidget* widget, gpointer data) {
    GtkWidget* dialog = gtk_file_chooser_dialog_new(
        "Open File",
        GTK_WINDOW(data),
        GTK_FILE_CHOOSER_ACTION_OPEN,
        "Cancel", GTK_RESPONSE_CANCEL,
        "Open", GTK_RESPONSE_ACCEPT,
        NULL);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        std::cout << "Selected file: " << filename << std::endl;
        file_clicked(filename);
        g_free(filename);
    }
    gtk_widget_destroy(dialog);
}

void on_encode_button_clicked(GtkWidget* widget, gpointer data) {
    std::cout << "Encoding..." << std::endl;
    encode_clicked();
}

void on_upload_button_clicked(GtkWidget* widget, gpointer data) {
    std::cout << "Uploading..." << std::endl;
    upload_clicked();
}

int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "YTCodr");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 350);
    gtk_window_set_resizable(GTK_WINDOW(window), false);

    // Create a vertical box layout
    GtkWidget* vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20); // Vertical spacing
    gtk_container_set_border_width(GTK_CONTAINER(window), 20);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create the "Browse File" button
    GtkWidget* file_button = gtk_button_new_with_label("Browse File");
    gtk_widget_set_size_request(file_button, 200, 50);
    gtk_box_pack_start(GTK_BOX(vbox), file_button, FALSE, FALSE, 0);

    // Create the "Encode" and "Upload" buttons in the same row
    GtkWidget* hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    GtkWidget* encode_button = gtk_button_new_with_label("Encode");
    GtkWidget* upload_button = gtk_button_new_with_label("Upload");
    gtk_widget_set_size_request(encode_button, 100, 40);
    gtk_widget_set_size_request(upload_button, 100, 40);
    gtk_box_pack_start(GTK_BOX(hbox), encode_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), upload_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    // Add a separator line between buttons and entry
    GtkWidget* separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start(GTK_BOX(vbox), separator, FALSE, FALSE, 10);

    // Create the entry box for the YouTube link
    GtkWidget* entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Paste YouTube link here...");
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);

    // Create the "Decode" button
    GtkWidget* decode_button = gtk_button_new_with_label("Decode");
    gtk_widget_set_size_request(decode_button, 200, 40);
    gtk_box_pack_start(GTK_BOX(vbox), decode_button, FALSE, FALSE, 0);

    // Connect signals
    g_signal_connect(file_button, "clicked", G_CALLBACK(on_file_button_clicked), window);
    g_signal_connect(encode_button, "clicked", G_CALLBACK(on_encode_button_clicked), NULL);
    g_signal_connect(upload_button, "clicked", G_CALLBACK(on_upload_button_clicked), NULL);
    g_signal_connect(decode_button, "clicked", G_CALLBACK(on_decode_button_clicked), entry);

    // Close the application when the window is closed
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Show all widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();

    return 0;
}
