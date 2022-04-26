/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package proxy;

import java.util.Arrays;

/**
 *
 * @author kival
 */
public class ClientDatabase implements Database {

    private Database serverDB = new ServerDatabase();

    @Override
    public void add(String query) throws Exception {
        System.out.println("Sanitising input for adding " + query + " into query.");
        this.serverDB.add(query);
    }

    @Override
    public void read(String query) throws Exception {
        if (query == "secret information") {
            throw new Exception("You are not allowed to read this information.");
        }

        this.serverDB.read(query);
    }
}
