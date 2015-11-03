<?php
/*
 +--------------------------------------------------------------------+
 | CiviCRM version 4.7                                                |
 +--------------------------------------------------------------------+
 | This file is a part of CiviCRM.                                    |
 |                                                                    |
 | CiviCRM is free software; you can copy, modify, and distribute it  |
 | under the terms of the GNU Affero General Public License           |
 | Version 3, 19 November 2007 and the CiviCRM Licensing Exception.   |
 |                                                                    |
 | CiviCRM is distributed in the hope that it will be useful, but     |
 | WITHOUT ANY WARRANTY; without even the implied warranty of         |
 | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.               |
 | See the GNU Affero General Public License for more details.        |
 |                                                                    |
 | You should have received a copy of the GNU Affero General Public   |
 | License and the CiviCRM Licensing Exception along                  |
 | with this program; if not, contact CiviCRM LLC                     |
 | at info[AT]civicrm[DOT]org. If you have questions about the        |
 | GNU Affero General Public License or the licensing of CiviCRM,     |
 | see the CiviCRM license FAQ at http://civicrm.org/licensing        |
 +--------------------------------------------------------------------+
*/

/**
 * sort handler to properly pass the field type for date fields.
 *
 */
class civicrm_handler_sort_address_pseudoconstant extends views_handler_sort {
  /**
   * The table alias of the additional joined table.
   *
   * @var _join_alias
   */
  private   $_join_alias;

  /**
   * The additional table to be joined.
   *
   * @var _join_table
   */
  protected $_join_table;
  
  /**
   * The field in the additional table to use in joining to civirm_address.
   *
   * @var _join_field
   */
  protected $_join_field;

  /**
   * The field in civicrm_address to use in joining the additional table.
   *
   * @var _join_left_field
   */
  protected $_join_left_field;

  function ensure_my_table() {
    $alias = parent::ensure_my_table();

    // Use the relationship if one is specified; otherwise, use the base table_alias.
    $relationship_id = (array_key_exists('relationship', $this->options) ? $this->options['relationship'] : '');
    if ($relationship_id && $relationship_id != 'none') {
      $table_alias = $this->view->relationship[$relationship_id]->table_alias;
    }
    else {
      $table_alias = $this->table_alias;
    }

    // Create a new join object and provide it with information about the join
    $join = new views_join();
    $join->construct($this->_join_table, $table_alias, $this->_join_left_field, $this->_join_field, NULL, 'LEFT');

    // Define an alias and use add_reliationship to add the join to the query.
    $this->_join_alias = $this->_join_table . '_' . $this->table;
    $join_table_alias = $this->query->add_relationship($this->_join_alias, $join, $table_alias, $this->relationship);

    return $table_alias;
  }

  function query() {
    $this->ensure_my_table();
    $this->query->add_orderby($this->_join_alias, 'name', $this->options['order']);
  }

}

