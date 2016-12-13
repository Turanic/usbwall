/**
 * \file devuser.h
 * \brief Contain user management functions
 **/

#pragma once

#include <misc/linked_list.h>

#include "ldap_config.h"

/**
 * \brief Retrieve the current user name.
 * \return users names connected on the system. Return NULL on error.
 *
 * usernames is extracted from utmp.
 */
struct linked_list *usernames_get(void);

/**
 * \brief Wait for a user to login and return his name.
 * \param socket_fd Unix Domain Socket used to receive notifications
 * \return name of users connected on the system. Return NULL on error.
 *
 * The function wait for an event from the pam module,
 * it will block until something is received.
 * Then, usernames_get is called and users names are returned.
 */
struct linked_list *wait_for_logging(int socket_fd);

/**
 * \brief Extract the list of usb serial ids allowed by
 *    the user.
 * \param username name of the checked user
 * \param cfg current ldap configuration
 * \return Linked list containing serial ids as char *.
 *  NULL if an error occured.
 *
 * The function will try to bind to the ldap server and
 * retrieved the devids from the given username. In the
 * case of a connection problem, NULL is returned.
 */
struct linked_list *devids_get(const char *username,
                               const struct ldap_cfg *cfg);

/**
 * \brief Take a devid and a list of devids and check if the given devid
 * is contained in devids. That said, it check if the devid is allowed
 * for the current user.
 *
 * \param devid  the devid to be checked
 * \param devids  list of devids (char *) allowed for the current user
 *
 * \return 1 if the device is allowed, 0 otherwhise
 */
int check_devid(const char *devid, struct linked_list *devids);
