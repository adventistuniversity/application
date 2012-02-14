<?php
// $Id$

/**
 * @file
 * FHCHS General College Application
 *
 * Page 1.
 * 
 */
function application_form_page1($form_state) {
  global $user;
  $form = array();
  _application_form_page1_load_defaults($form_state);
  ahah_helper_register($form, $form_state);
  $states = sonisweb_integration_dropbox_to_form_api_options_array(
              sonisweb_integration_api("CFC.drp_box", "state", "no", array(array('sonis_ds', '#sonis.ds#'),
                                       array('allow_blank', "yes"),
                                       array('hide', "no"),
                                       array('multi_select', "no"),
                                       array('Additional_Properties', ""),
                                       array('hide_excludes', 'yes'))));
  $countries = sonisweb_integration_dropbox_to_form_api_options_array(
                  sonisweb_integration_api("CFC.drp_box", "country", "no", array(array('sonis_ds', '#sonis.ds#'),
                                           array('allow_blank', "yes"),
                                           array('hide', "no"),
                                           array('multi_select', "no"),
                                           array('Additional_Properties', ""),
                                           array('hide_excludes', 'yes'))));
//   print_r($form);
//   print_r($form_state);

//
// 
  $form['Name'] = array(
    '#type' => 'fieldset',
    '#title' => t('Name'),
    '#prefix' => '<div id="name-information-wrapper">', // This is our wrapper div.
    '#suffix' => '</div>',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['Name']['preferred'] = array(
    '#type' => 'textfield',
    '#title' => t('Preferred Name'),
    '#default_value' => $form_state['values']['preferred'],
    '#description' => "The name you would like us to refer to you by. For example, <em>Bob</em> if your first name is <em>Robert</em>.",
    '#maxlength' => 20,
  '#size' => 20,
  );
  $form['Name']['first'] = array(
    '#type' => 'textfield',
    '#title' => t('Legal First Name'),
    '#default_value' => $form_state['values']['first'],
    '#required' => TRUE,
    '#maxlength' => 30,
    '#size' => 30,
  );
  $form['Name']['middle'] = array(
    '#type' => 'textfield',
    '#title' => t('Middle Name'),
    '#default_value' => $form_state['values']['middle'],
    '#required' => FALSE,
    '#maxlength' => 15,
    '#size' => 15,
  );
  $form['Name']['last'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#default_value' => $form_state['values']['last'],
    '#required' => TRUE,
    '#maxlength' => 30,
    '#size' => 30,
  );
  $form['Name']['former_last'] = array(
    '#type' => 'textfield',
    '#description' => "Please list any previous last names. For example, Smith, Thompson.",
    '#title' => t('Former Last Name'),
    '#default_value' => $form_state['values']['former_last'],
    '#required' => FALSE,
    '#maxlength' => 30,
    '#size' => 30,
  );
  
  
// Contact Information
  $form['Contact_Information'] = array(
    '#type' => 'fieldset',
    '#title' => t('Contact Information'),
  '#prefix' => '<div id="contact-information-wrapper">', // This is our wrapper div.
    '#suffix' => '</div>',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['Contact_Information']['countryofresidence'] = array(
    '#type' => 'select',
    '#title' => t('Country of Residence'),
    '#default_value' => ($form_state['values']['countryofresidence'] == ""?"UNITED STATES":$form_state['values']['countryofresidence']),
  '#ahah' => array(
     'path' => ahah_helper_path(array('Contact_Information')),
     'wrapper' => 'contact-information-wrapper',
     'method' => 'replace',
     'event' => 'change',
     'effect' => 'fade',
    ),
    '#options' => $countries,
    '#required' => TRUE,
  );
  $form['Contact_Information']['update_countryofresidence'] = array(
    '#type' => 'submit',
    '#value' => t('Country of Residence'),
    '#submit' => array('ahah_helper_generic_submit'),
    '#attributes' => array('class' => 'no-js'),
  );
  $form['Contact_Information']['streetaddress'] = array(
    '#type' => 'textfield',
    '#title' => t('Street Address'),
    '#default_value' => $form_state['values']['streetaddress'],
    '#required' => TRUE,
    '#maxlength' => 35,
    '#size' => 35,
  );
  $form['Contact_Information']['addresscity'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#default_value' => $form_state['values']['addresscity'],
    '#required' => TRUE,
    '#maxlength' => 35,
    '#size' => 35,
  );
  if ($form_state['values']['countryofresidence'] == "" || strcasecmp($form_state['values']['countryofresidence'], "UNITED STATES") == 0
      || strcasecmp($form_state['values']['countryofresidence'], "American Samoa") == 0 || strcasecmp($form_state['values']['countryofresidence'], "Federated States of Micronesia") == 0
      || strcasecmp($form_state['values']['countryofresidence'], "Guam") == 0 || strcasecmp($form_state['values']['countryofresidence'], "U.S. Minor Outlying Is") == 0
      || strcasecmp($form_state['values']['countryofresidence'], "Puerto Rico") == 0) {
    $form['Contact_Information']['state'] = array(
      '#type' => 'select',
      '#title' => t('State'),
      '#default_value' => $form_state['values']['state'],
      '#options' => $states,
      '#required' => TRUE,
    );
  }
  $form['Contact_Information']['postalcode'] = array(
    '#type' => 'textfield',
    '#title' => t('Postal Code'),
    '#default_value' => $form_state['values']['postalcode'],
    '#required' => TRUE,
    '#maxlength' => 10,
    '#size' => 10,
  );
  $form['Contact_Information']['primaryphone'] = array(
    '#type' => 'textfield',
    '#title' => t('Primary Phone Number'),
    '#default_value' => $form_state['values']['primaryphone'],
    '#required' => TRUE,
    '#description' => "The first number we should dial when trying to reach you.",
    '#maxlength' => 15,
    '#size' => 15,
  );
  $form['Contact_Information']['cellphone'] = array(
    '#type' => 'textfield',
    '#title' => t('Cell Phone Number'),
    '#default_value' => $form_state['values']['cellphone'],
    '#required' => False,
    '#description' => "Mobile phone number we should dial when trying to reach you.",
    '#maxlength' => 15,
    '#size' => 15,
  );
  $form['Contact_Information']['alternatephone'] = array(
    '#type' => 'textfield',
    '#title' => t('Alternate Phone Number'),
    '#default_value' => $form_state['values']['alternatephone'],
    '#required' => FALSE,
    '#description' => "If we can't reach you at the first number, we'll try this one.",
    '#maxlength' => 15,
    '#size' => 15,
  );
  $form['Contact_Information']['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email Address'),
    '#default_value' => ($form_state['values']['email'] == ""?$user->mail:$form_state['values']['email']),
    '#required' => FALSE,
    '#description' => "",
    '#maxlength' => 100,
    '#size' => 35,
  );
  
// Get authorize person
$form['authorized_person'] = array(
   '#type' => 'fieldset',
   '#title' => t('Authorized Person'),
   '#prefix' => '<div id="authorized-person-wrapper">', // This is our wrapper div.
   '#suffix' => '</div>',
   '#collapsible' => FALSE,
   '#collapsed' => FALSE,
 );

$form['authorized_person']['person1_first_name'] = array(
  '#type' => 'textfield',
  '#title' => t('First Name'),
  '#default_value' => $form_state['values']['person1_first_name'],
  '#required' => FALSE,
  '#maxlength' => 30,
  '#size' => 30,
);

$form['authorized_person']['person1_last_name'] = array(
  '#type' => 'textfield',
  '#title' => t('Last Name'),
  '#default_value' => $form_state['values']['person1_last_name'],
  '#required' => FALSE,
  '#maxlength' => 30,
  '#size' => 30,
);

$form['authorized_person']['person1_relationship'] = array(
  '#type' => 'textfield',
  '#title' => t('Relationship'),
  '#description' => t('Enter the person relationship to you.'),
  '#default_value' => $form_state['values']['person1_last_name'],
  '#required' => FALSE,
  '#maxlength' => 50,
  '#size' => 50,
);


$form['authorized_person']['person2_first_name'] = array(
  '#type' => 'textfield',
  '#title' => t('First Name'),
  '#default_value' => $form_state['values']['person1_first_name'],
  '#required' => FALSE,
  '#maxlength' => 30,
  '#size' => 30,
);

$form['authorized_person']['person2_last_name'] = array(
  '#type' => 'textfield',
  '#title' => t('Last Name'),
  '#default_value' => $form_state['values']['person1_last_name'],
  '#required' => FALSE,
  '#maxlength' => 30,
  '#size' => 30,
);

$form['authorized_person']['person2_relationship'] = array(
  '#type' => 'textfield',
  '#title' => t('Relationship'),
  '#description' => t('Enter the person relationship to you.'),
  '#default_value' => $form_state['values']['person1_last_name'],
  '#required' => FALSE,
  '#maxlength' => 50,
  '#size' => 50,
);

// Licensure Eligibility
$form['Licensure Eligibility'] = array(
   '#type' => 'fieldset',
   '#title' => t('Background Information'),
 '#prefix' => '<div id="licensure-eligibility-wrapper">', // This is our wrapper div.
   '#suffix' => '</div>',
   '#collapsible' => FALSE,
   '#collapsed' => FALSE,
 );
$form['Licensure Eligibility']['felony'] = array(
  '#type' => 'select',
  '#title' => t('Have you ever been convicted of, plea bargained, entered a plea of nolo contendere or no contest to, had adjudication withheld for or participated in a pre-trial diversion program for a crime, excluding any misdeameanor traffic offenses?'),
  '#description' => t('(Answering yes will not automatically disqualify an individual from admission to FHCHS; however, it may prevent a graduate from taking certification/licensing exams.)'),
  '#default_value' => $form_state['values']['felony'],
  '#required' => TRUE,
  '#options' => array(
    '' => '',
    '1' => t('Yes'),
    '0' => t('No')
    ),
);

// Native Language
//Language is a two step question
$form['Native_Language'] = array(
   '#type' => 'fieldset',
   '#title' => t('Language'),
   '#prefix' => '<div id="native-language-wrapper">', // This is our wrapper div.
   '#suffix' => '</div>',
   '#collapsible' => FALSE,
   '#collapsed' => FALSE,
 );
$form['Native_Language']['language'] = array(
  '#type' => 'select',
  '#title' => t('Is English your primary language?'),
  '#default_value' => $form_state['values']['language'],
  '#required' => TRUE,
      '#ahah' => array(
    'path' => ahah_helper_path(array('Native_Language')),
    'wrapper' => 'native-language-wrapper',
    'method' => 'replace',
    'event' => 'change',
    'effect' => 'fade',
    ),
  '#options' => array(
    '' => '',
    '1' => t('Yes'),
    '0' => t('No')
    ),
);

$form['Native_Language']['update_language'] = array(
  '#type' => 'submit',
  '#value' => t('language'),
  // Note that we can simply use the generic submit callback provided by the
  // ahah_helper module here!
  // All it does, is set $form_state['rebuild'] = TRUE.
  '#submit' => array('ahah_helper_generic_submit'),
  // We set the 'no-js' class, which means this submit button will be hidden
  // automatically by Drupal if JS is enabled.
  '#attributes' => array('class' => 'no-js'),
);
if ($form_state['values']['language'] == "0") {
  $form['Native_Language']['nativelanguage'] = array(
    '#type' => 'select',
    '#title' => t('Native_Language'),
    '#default_value' => $form_state['values']['nativelanguage'],
    '#required' => TRUE,
    '#options' => array(
      '' => t(''),
      'abk' => t('Abkhaz'),
      'ace' => t('Achinese'),
      'ach' => t('Acoli'),
      'ada' => t('Adangme'),
      'ady' => t('Adygei'),
      'aar' => t('Afar'),
      'afh' => t('Afrihili (Artificial language)'),
      'afr' => t('Afrikaans'),
      'afa' => t('Afroasiatic (Other)'),
      'ain' => t('Ainu'),
      'aka' => t('Akan'),
      'akk' => t('Akkadian'),
      'alb' => t('Albanian'),
      'ale' => t('Aleut'),
      'alg' => t('Algonquian (Other)'),
      'alt' => t('Altai'),
      'tut' => t('Altaic (Other)'),
      'amh' => t('Amharic'),
      'anp' => t('Angika'),
      'apa' => t('Apache languages'),
      'ara' => t('Arabic'),
      'arg' => t('Aragonese Spanish'),
      'arc' => t('Aramaic'),
      'arp' => t('Arapaho'),
      'arw' => t('Arawak'),
      'arm' => t('Armenian'),
      'rup' => t('Aromanian'),
      'art' => t('Artificial (Other)'),
      'asm' => t('Assamese'),
      'ath' => t('Athapascan (Other)'),
      'aus' => t('Australian languages'),
      'map' => t('Austronesian (Other)'),
      'ava' => t('Avaric'),
      'ave' => t('Avestan'),
      'awa' => t('Awadhi'),
      'aym' => t('Aymara'),
      'aze' => t('Azerbaijani'),
      'ast' => t('Bable'),
      'ban' => t('Balinese'),
      'bat' => t('Baltic (Other)'),
      'bal' => t('Baluchi'),
      'bam' => t('Bambara'),
      'bai' => t('Bamileke languages'),
      'bad' => t('Banda languages'),
      'bnt' => t('Bantu (Other)'),
      'bas' => t('Basa'),
      'bak' => t('Bashkir'),
      'baq' => t('Basque'),
      'btk' => t('Batak'),
      'bej' => t('Beja'),
      'bel' => t('Belarusian'),
      'bem' => t('Bemba'),
      'ben' => t('Bengali'),
      'ber' => t('Berber (Other)'),
      'bho' => t('Bhojpuri'),
      'bih' => t('Bihari'),
      'bik' => t('Bikol'),
      'byn' => t('Bilin'),
      'bis' => t('Bislama'),
      'zbl' => t('Blissymbolics'),
      'bos' => t('Bosnian'),
      'bra' => t('Braj'),
      'bre' => t('Breton'),
      'bug' => t('Bugis'),
      'bul' => t('Bulgarian'),
      'bua' => t('Buriat'),
      'bur' => t('Burmese'),
      'cad' => t('Caddo'),
      'car' => t('Carib'),
      'cat' => t('Catalan'),
      'cau' => t('Caucasian (Other)'),
      'ceb' => t('Cebuano'),
      'cel' => t('Celtic (Other)'),
      'cai' => t('Central American Indian (Other)'),
      'chg' => t('Chagatai'),
      'cmc' => t('Chamic languages'),
      'cha' => t('Chamorro'),
      'che' => t('Chechen'),
      'chr' => t('Cherokee'),
      'chy' => t('Cheyenne'),
      'chb' => t('Chibcha'),
      'chi' => t('Chinese'),
      'chn' => t('Chinook jargon'),
      'chp' => t('Chipewyan'),
      'cho' => t('Choctaw'),
      'chu' => t('Church Slavic'),
      'chk' => t('Chuukese'),
      'chv' => t('Chuvash'),
      'cop' => t('Coptic'),
      'cor' => t('Cornish'),
      'cos' => t('Corsican'),
      'cre' => t('Cree'),
      'mus' => t('Creek'),
      'crp' => t('Creoles and Pidgins (Other)'),
      'cpe' => t('Creoles and Pidgins, English-based (Other)'),
      'cpf' => t('Creoles and Pidgins, French-based (Other)'),
      'cpp' => t('Creoles and Pidgins, Portuguese-based (Other)'),
      'crh' => t('Crimean Tatar'),
      'scr' => t('Croatian'),
      'cus' => t('Cushitic (Other)'),
      'cze' => t('Czech'),
      'dak' => t('Dakota'),
      'dan' => t('Danish'),
      'dar' => t('Dargwa'),
      'day' => t('Dayak'),
      'del' => t('Delaware'),
      'din' => t('Dinka'),
      'div' => t('Divehi'),
      'doi' => t('Dogri'),
      'dgr' => t('Dogrib'),
      'dra' => t('Dravidian (Other)'),
      'dua' => t('Duala'),
      'dut' => t('Dutch'),
      'dum' => t('Dutch, Middle (ca. 1050-1350)'),
      'dyu' => t('Dyula'),
      'dzo' => t('Dzongkha'),
      'frs' => t('East Frisian'),
      'bin' => t('Edo'),
      'efi' => t('Efik'),
      'egy' => t('Egyptian'),
      'eka' => t('Ekajuk'),
      'elx' => t('Elamite'),
      'eng' => t('English'),
      'enm' => t('English, Middle (1100-1500)'),
      'ang' => t('English, Old (ca. 450-1100)'),
      'myv' => t('Erzya'),
      'epo' => t('Esperanto'),
      'est' => t('Estonian'),
      'gez' => t('Ethiopic'),
      'ewe' => t('Ewe'),
      'ewo' => t('Ewondo'),
      'fan' => t('Fang'),
      'fat' => t('Fanti'),
      'fao' => t('Faroese'),
      'fij' => t('Fijian'),
      'fil' => t('Filipino'),
      'fin' => t('Finnish'),
      'fiu' => t('Finno-Ugrian (Other)'),
      'fon' => t('Fon'),
      'fre' => t('French'),
      'frm' => t('French, Middle (ca. 1300-1600)'),
      'fro' => t('French, Old (ca. 842-1300)'),
      'fry' => t('Frisian'),
      'fur' => t('Friulian'),
      'ful' => t('Fula'),
      'gaa' => t('Ga'),
      'glg' => t('Galician'),
      'lug' => t('Ganda'),
      'gay' => t('Gayo'),
      'gba' => t('Gbaya'),
      'geo' => t('Georgian'),
      'ger' => t('German'),
      'gmh' => t('German, Middle High (ca. 1050-1500)'),
      'goh' => t('German, Old High (ca. 750-1050)'),
      'gem' => t('Germanic (Other)'),
      'gil' => t('Gilbertese'),
      'gon' => t('Gondi'),
      'gor' => t('Gorontalo'),
      'got' => t('Gothic'),
      'grb' => t('Grebo'),
      'grc' => t('Greek, Ancient (to 1453)'),
      'gre' => t('Greek, Modern (1453- )'),
      'grn' => t('Guarani'),
      'guj' => t('Gujarati'),
      'gwi' => t('Gwich\'in'),
      'hai' => t('Haida'),
      'hat' => t('Haitian French Creole'),
      'hau' => t('Hausa'),
      'haw' => t('Hawaiian'),
      'heb' => t('Hebrew'),
      'her' => t('Herero'),
      'hil' => t('Hiligaynon'),
      'him' => t('Himachali'),
      'hin' => t('Hindi'),
      'hmo' => t('Hiri Motu'),
      'hit' => t('Hittite'),
      'hmn' => t('Hmong'),
      'hun' => t('Hungarian'),
      'hup' => t('Hupa'),
      'iba' => t('Iban'),
      'ice' => t('Icelandic'),
      'ido' => t('Ido'),
      'ibo' => t('Igbo'),
      'ijo' => t('Ijo'),
      'ilo' => t('Iloko'),
      'smn' => t('Inari Sami'),
      'inc' => t('Indic (Other)'),
      'ine' => t('Indo-European (Other)'),
      'ind' => t('Indonesian'),
      'inh' => t('Ingush'),
      'ina' => t('Interlingua (International Auxiliary Language Association)'),
      'ile' => t('Interlingue'),
      'iku' => t('Inuktitut'),
      'ipk' => t('Inupiaq'),
      'ira' => t('Iranian (Other)'),
      'gle' => t('Irish'),
      'mga' => t('Irish, Middle (ca. 1100-1550)'),
      'sga' => t('Irish, Old (to 1100)'),
      'iro' => t('Iroquoian (Other)'),
      'ita' => t('Italian'),
      'jpn' => t('Japanese'),
      'jav' => t('Javanese'),
      'jrb' => t('Judeo-Arabic'),
      'jpr' => t('Judeo-Persian'),
      'kbd' => t('Kabardian'),
      'kab' => t('Kabyle'),
      'kac' => t('Kachin'),
      'kal' => t('Kalatdlisut'),
      'kam' => t('Kamba'),
      'kan' => t('Kannada'),
      'kau' => t('Kanuri'),
      'krc' => t('Karachay-Balkar'),
      'kaa' => t('Kara-Kalpak'),
      'krl' => t('Karelian'),
      'kar' => t('Karen languages'),
      'kas' => t('Kashmiri'),
      'csb' => t('Kashubian'),
      'kaw' => t('Kawi'),
      'kaz' => t('Kazakh'),
      'kha' => t('Khasi'),
      'khm' => t('Khmer'),
      'khi' => t('Khoisan (Other)'),
      'kho' => t('Khotanese'),
      'kik' => t('Kikuyu'),
      'kmb' => t('Kimbundu'),
      'kin' => t('Kinyarwanda'),
      'tlh' => t('Klingon (Artificial language)'),
      'kom' => t('Komi'),
      'kon' => t('Kongo'),
      'kok' => t('Konkani'),
      'kut' => t('Kootenai'),
      'kor' => t('Korean'),
      'kpe' => t('Kpelle'),
      'kro' => t('Kru (Other)'),
      'kua' => t('Kuanyama'),
      'kum' => t('Kumyk'),
      'kur' => t('Kurdish'),
      'kru' => t('Kurukh'),
      'kos' => t('Kusaie'),
      'kir' => t('Kyrgyz'),
      'lad' => t('Ladino'),
      'lah' => t('Lahnda'),
      'lam' => t('Lamba (Zambia and Congo)'),
      'lao' => t('Lao'),
      'lat' => t('Latin'),
      'lav' => t('Latvian'),
      'lez' => t('Lezgian'),
      'lim' => t('Limburgish'),
      'lin' => t('Lingala'),
      'lit' => t('Lithuanian'),
      'jbo' => t('Lojban (Artificial language)'),
      'nds' => t('Low German'),
      'dsb' => t('Lower Sorbian'),
      'loz' => t('Lozi'),
      'lub' => t('Luba-Katanga'),
      'lua' => t('Luba-Lulua'),
      'lui' => t('Luiseno'),
      'smj' => t('Lule Sami'),
      'lun' => t('Lunda'),
      'luo' => t('Luo (Kenya and Tanzania)'),
      'lus' => t('Lushai'),
      'ltz' => t('Luxembourgish'),
      'mac' => t('Macedonian'),
      'mad' => t('Madurese'),
      'mag' => t('Magahi'),
      'mai' => t('Maithili'),
      'mak' => t('Makasar'),
      'mlg' => t('Malagasy'),
      'may' => t('Malay'),
      'mal' => t('Malayalam'),
      'mlt' => t('Maltese'),
      'mnc' => t('Manchu'),
      'mdr' => t('Mandar'),
      'man' => t('Mandingo'),
      'mni' => t('Manipuri'),
      'mno' => t('Manobo languages'),
      'glv' => t('Manx'),
      'mao' => t('Maori'),
      'arn' => t('Mapuche'),
      'mar' => t('Marathi'),
      'chm' => t('Mari'),
      'mah' => t('Marshallese'),
      'mwr' => t('Marwari'),
      'mas' => t('Masai'),
      'myn' => t('Mayan languages'),
      'men' => t('Mende'),
      'mic' => t('Micmac'),
      'min' => t('Minangkabau'),
      'mwl' => t('Mirandese'),
      'mis' => t('Miscellaneous languages'),
      'moh' => t('Mohawk'),
      'mdf' => t('Moksha'),
      'mol' => t('Moldavian'),
      'mon' => t('Mongolian'),
      'lol' => t('Mongo-Nkundu'),
      'mkh' => t('Mon-Khmer (Other)'),
      'mos' => t('Moore'),
      'mul' => t('Multiple languages'),
      'mun' => t('Munda (Other)'),
      'nah' => t('Nahuatl'),
      'nau' => t('Nauru'),
      'nav' => t('Navajo'),
      'nbl' => t('Ndebele (South Africa)'),
      'nde' => t('Ndebele (Zimbabwe)'),
      'ndo' => t('Ndonga'),
      'nap' => t('Neapolitan Italian'),
      'nep' => t('Nepali'),
      'new' => t('Newari'),
      'nwc' => t('Newari, Old'),
      'nia' => t('Nias'),
      'nic' => t('Niger-Kordofanian (Other)'),
      'ssa' => t('Nilo-Saharan (Other)'),
      'niu' => t('Niuean'),
      'nqo' => t('N\'Ko'),
      'zxx' => t('No linguistic content'),
      'nog' => t('Nogai'),
      'nai' => t('North American Indian (Other)'),
      'frr' => t('North Frisian'),
      'sme' => t('Northern Sami'),
      'nso' => t('Northern Sotho'),
      'nor' => t('Norwegian'),
      'nob' => t('Norwegian (Bokmal)'),
      'nno' => t('Norwegian (Nynorsk)'),
      'nub' => t('Nubian languages'),
      'nym' => t('Nyamwezi'),
      'nya' => t('Nyanja'),
      'nyn' => t('Nyankole'),
      'nyo' => t('Nyoro'),
      'nzi' => t('Nzima'),
      'oci' => t('Occitan (post 1500)'),
      'xal' => t('Oirat'),
      'oji' => t('Ojibwa'),
      'non' => t('Old Norse'),
      'peo' => t('Old Persian (ca. 600-400 B.C.)'),
      'ori' => t('Oriya'),
      'orm' => t('Oromo'),
      'osa' => t('Osage'),
      'oss' => t('Ossetic'),
      'oto' => t('Otomian languages'),
      'pal' => t('Pahlavi'),
      'pau' => t('Palauan'),
      'pli' => t('Pali'),
      'pam' => t('Pampanga'),
      'pag' => t('Pangasinan'),
      'pan' => t('Panjabi'),
      'pap' => t('Papiamento'),
      'paa' => t('Papuan (Other)'),
      'per' => t('Persian'),
      'phi' => t('Philippine (Other)'),
      'phn' => t('Phoenician'),
      'pol' => t('Polish'),
      'pon' => t('Ponape'),
      'por' => t('Portuguese'),
      'pra' => t('Prakrit languages'),
      'pro' => t('Provencal (to 1500)'),
      'pus' => t('Pushto'),
      'que' => t('Quechua'),
      'roh' => t('Raeto-Romance'),
      'raj' => t('Rajasthani'),
      'rap' => t('Rapanui'),
      'rar' => t('Rarotongan'),
      'roa' => t('Romance (Other)'),
      'rom' => t('Romani'),
      'rum' => t('Romanian'),
      'run' => t('Rundi'),
      'rus' => t('Russian'),
      'sal' => t('Salishan languages'),
      'sam' => t('Samaritan Aramaic'),
      'smi' => t('Sami'),
      'smo' => t('Samoan'),
      'sad' => t('Sandawe'),
      'sag' => t('Sango (Ubangi Creole)'),
      'san' => t('Sanskrit'),
      'sat' => t('Santali'),
      'srd' => t('Sardinian'),
      'sas' => t('Sasak'),
      'sco' => t('Scots'),
      'gla' => t('Scottish Gaelic'),
      'sel' => t('Selkup'),
      'sem' => t('Semitic (Other)'),
      'scc' => t('Serbian'),
      'srr' => t('Serer'),
      'shn' => t('Shan'),
      'sna' => t('Shona'),
      'iii' => t('Sichuan Yi'),
      'scn' => t('Sicilian Italian'),
      'sid' => t('Sidamo'),
      'sgn' => t('Sign languages'),
      'bla' => t('Siksika'),
      'snd' => t('Sindhi'),
      'sin' => t('Sinhalese'),
      'sit' => t('Sino-Tibetan (Other)'),
      'sio' => t('Siouan (Other)'),
      'sms' => t('Skolt Sami'),
      'den' => t('Slave'),
      'sla' => t('Slavic (Other)'),
      'slo' => t('Slovak'),
      'slv' => t('Slovenian'),
      'sog' => t('Sogdian'),
      'som' => t('Somali'),
      'son' => t('Songhai'),
      'snk' => t('Soninke'),
      'wen' => t('Sorbian (Other)'),
      'sot' => t('Sotho'),
      'sai' => t('South American Indian (Other)'),
      'sma' => t('Southern Sami'),
      'spa' => t('Spanish'),
      'srn' => t('Sranan'),
      'suk' => t('Sukuma'),
      'sux' => t('Sumerian'),
      'sun' => t('Sundanese'),
      'sus' => t('Susu'),
      'swa' => t('Swahili'),
      'ssw' => t('Swazi'),
      'swe' => t('Swedish'),
      'gsw' => t('Swiss German'),
      'syc' => t('Syriac'),
      'syr' => t('Syriac, Modern'),
      'tgl' => t('Tagalog'),
      'tah' => t('Tahitian'),
      'tai' => t('Tai (Other)'),
      'tgk' => t('Tajik'),
      'tmh' => t('Tamashek'),
      'tam' => t('Tamil'),
      'tat' => t('Tatar'),
      'tel' => t('Telugu'),
      'tem' => t('Temne'),
      'ter' => t('Terena'),
      'tet' => t('Tetum'),
      'tha' => t('Thai'),
      'tib' => t('Tibetan'),
      'tig' => t('Tigre'),
      'tir' => t('Tigrinya'),
      'tiv' => t('Tiv'),
      'tli' => t('Tlingit'),
      'tpi' => t('Tok Pisin'),
      'tkl' => t('Tokelauan'),
      'tog' => t('Tonga (Nyasa)'),
      'ton' => t('Tongan'),
      'tsi' => t('Tsimshian'),
      'tso' => t('Tsonga'),
      'tsn' => t('Tswana'),
      'tum' => t('Tumbuka'),
      'tup' => t('Tupi languages'),
      'tur' => t('Turkish'),
      'ota' => t('Turkish, Ottoman'),
      'tuk' => t('Turkmen'),
      'tvl' => t('Tuvaluan'),
      'tyv' => t('Tuvinian'),
      'twi' => t('Twi'),
      'udm' => t('Udmurt'),
      'uga' => t('Ugaritic'),
      'uig' => t('Uighur'),
      'ukr' => t('Ukrainian'),
      'umb' => t('Umbundu'),
      'und' => t('Undetermined'),
      'hsb' => t('Upper Sorbian'),
      'urd' => t('Urdu'),
      'uzb' => t('Uzbek'),
      'vai' => t('Vai'),
      'ven' => t('Venda'),
      'vie' => t('Vietnamese'),
      'vol' => t('Volapuk'),
      'vot' => t('Votic'),
      'wak' => t('Wakashan languages'),
      'wln' => t('Walloon'),
      'war' => t('Waray'),
      'was' => t('Washo'),
      'wel' => t('Welsh'),
      'wal' => t('Wolayta'),
      'wol' => t('Wolof'),
      'xho' => t('Xhosa'),
      'sah' => t('Yakut'),
      'yao' => t('Yao (Africa)'),
      'yap' => t('Yapese'),
      'yid' => t('Yiddish'),
      'yor' => t('Yoruba'),
      'ypk' => t('Yupik languages'),
      'znd' => t('Zande languages'),
      'zap' => t('Zapotec'),
      'zza' => t('Zaza'),
      'zen' => t('Zenaga'),
      'zha' => t('Zhuang'),
      'zul' => t('Zulu'),
      'zun' => t('Zuni')
    ),
    '#description' => t('Proof of English proficiency is required for admission.')
  );
}
  
// Birthplace Information
  $form['Birthplace_Information'] = array(
    '#type' => 'fieldset',
    '#title' => t('Birthplace Information'),
    '#prefix' => '<div id="birthplace-information-wrapper">', // This is our wrapper div.
    '#suffix' => '</div>',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['Birthplace_Information']['dateofbirth'] = array(
    '#type' => 'date',
    '#title' => t('Date of Birth'),
    '#default_value' => $form_state['values']['dateofbirth'],//isset($form_state['values']['dateofbirth']) ? date('Y-m-d', strtotime($form_state['values']['dateofbirth'])):'',
    //'#date_format' => 'm/d/Y',
    //'#date_year_range' => '-100:-12',
    '#required' => TRUE,
  );
  $form['Birthplace_Information']['countryofbirth'] = array(
    '#type' => 'select',
    '#title' => t('Country of Birth'),
    '#default_value' => ($form_state['values']['countryofbirth'] == ""?"UNITED STATES":$form_state['values']['countryofbirth']),
    '#options' => $countries,
   '#ahah' => array(
     'path' => ahah_helper_path(array('Birthplace_Information')),
     'wrapper' => 'birthplace-information-wrapper',
     'method' => 'replace',
     'event' => 'change',
     'effect' => 'fade',
    ),
    '#required' => TRUE,
  );
  $form['Birthplace_Information']['update_countryofbirth'] = array(
    '#type' => 'submit',
    '#value' => t('Country of Birth'),
    // Note that we can simply use the generic submit callback provided by the
    // ahah_helper module here!
    // All it does, is set $form_state['rebuild'] = TRUE.
    '#submit' => array('ahah_helper_generic_submit'),
    // We set the 'no-js' class, which means this submit button will be hidden
    // automatically by Drupal if JS is enabled.
    '#attributes' => array('class' => 'no-js'),
  );

  if ($form_state['values']['countryofbirth'] == "" || strcasecmp($form_state['values']['countryofbirth'], "UNITED STATES") == 0
      || strcasecmp($form_state['values']['countryofbirth'], "American Samoa") == 0 || strcasecmp($form_state['values']['countryofbirth'], "Federated States of Micronesia") == 0
      || strcasecmp($form_state['values']['countryofbirth'], "Guam") == 0 || strcasecmp($form_state['values']['countryofbirth'], "U.S. Minor Outlying Is") == 0
      || strcasecmp($form_state['values']['countryofbirth'], "Puerto Rico") == 0) {
    $form['Birthplace_Information']['cityofbirth'] = array(
      '#type' => 'textfield',
      '#title' => t('City or Province of Birth'),
      '#default_value' => $form_state['values']['cityofbirth'],
      '#required' => TRUE,
      '#maxlength' => 35,
      '#size' => 35,
    );
    $form['Birthplace_Information']['stateofbirth'] = array(
      '#type' => 'select',
      '#title' => t('State of Birth'),
      '#default_value' => $form_state['values']['stateofbirth'],
      '#options' => $states,
      '#required' => TRUE,
    );
    $form['Birthplace_Information']['ssn'] = array(
      '#type' => 'textfield',
      '#title' => t('Social Security Number or Naturalized U.S. Citizen Number'),
      '#default_value' => $form_state['values']['ssn'],
      '#required' => TRUE,
      '#maxlength' => 9,
      '#size' => 9,
    );
  }
  else {
    $form['Birthplace_Information']['cityofbirth'] = array(
      '#type' => 'textfield',
      '#title' => t('City or Province of Birth'),
      '#default_value' => $form_state['values']['cityofbirth'],
      '#required' => TRUE,
      '#maxlength' => 35,
      '#size' => 35,
    );

    $form['Birthplace_Information']['countryofcitizenship'] = array(
      '#type' => 'select',
      '#title' => t('Country of Citizenship'),
      '#default_value' => ($form_state['values']['countryofcitizenship'] == ""?$form_state['values']['countryofbirth']:$form_state['values']['countryofcitizenship']),
      '#ahah' => array(
        'path' => ahah_helper_path(array('Birthplace_Information')),
          'wrapper' => 'birthplace-information-wrapper',
          'method' => 'replace',
          'event' => 'change',
          'effect' => 'fade',
        ),
      '#options' => $countries,
      '#required' => FALSE,
    );
    $form['Birthplace_Information']['update_countryofcitizenship'] = array(
      '#type' => 'submit',
      '#value' => t('Country of Citizenship'),
      // Note that we can simply use the generic submit callback provided by the
      // ahah_helper module here!
      // All it does, is set $form_state['rebuild'] = TRUE.
      '#submit' => array('ahah_helper_generic_submit'),
      // We set the 'no-js' class, which means this submit button will be hidden
      // automatically by Drupal if JS is enabled.
      '#attributes' => array('class' => 'no-js'),
    );
    $form['Birthplace_Information']['numberquestion'] = array(
      '#type' => 'select',
      '#title' => t('Please indicate the US immigration or citizenship number you have'),
      '#default_value' => $form_state['values']['numberquestion'],
      '#options' => array(
        'Please Select' => t(''),
        'Does Not Apply' => t('Does Not Apply'),
        // US Social Security Number makes SS Field appear and Number field go away
        'US Social Security Number' => t('Have US Social Security Number'),
        'Permanent Resident Number' => t('Permanent Resident Number'),
        // Applied for and Online Only makes number field go away
        'Permanent Resident Number Applied For' => t('Permanent Resident Number Applied For'),
        'Taking Online Courses Only' => t('Taking Online Courses Only'),
        ),
        '#ahah' => array(
        'path' => ahah_helper_path(array('Birthplace_Information')),
          'wrapper' => 'birthplace-information-wrapper',
          'method' => 'replace',
          'event' => 'change',
          'effect' => 'fade',
        ),
      '#required' => TRUE,
    );
      $form['Birthplace_Information']['update_numberquestion'] = array(
      '#type' => 'submit',
      '#value' => t('Please indicate the US immigration or citizenship number you have'),
      // Note that we can simply use the generic submit callback provided by the
      // ahah_helper module here!
      // All it does, is set $form_state['rebuild'] = TRUE.
      '#submit' => array('ahah_helper_generic_submit'),
      // We set the 'no-js' class, which means this submit button will be hidden
      // automatically by Drupal if JS is enabled.
      '#attributes' => array('class' => 'no-js'),
    );
    if ($form_state['values']['numberquestion'] != "Taking Online Courses Only") {
      if (
			(strcasecmp($form_state['values']['countryofcitizenship'], "UNITED STATES") == 0
      || strcasecmp($form_state['values']['countryofcitizenship'], "American Samoa") == 0 || strcasecmp($form_state['values']['countryofcitizenship'], "Federated States of Micronesia") == 0
      || strcasecmp($form_state['values']['countryofcitizenship'], "Guam") == 0 || strcasecmp($form_state['values']['countryofcitizenship'], "U.S. Minor Outlying Is") == 0
      || strcasecmp($form_state['values']['countryofcitizenship'], "Puerto Rico") == 0) || $form_state['values']['numberquestion'] == "US Social Security Number") {
        $form['Birthplace_Information']['ssn'] = array(
          '#type' => 'textfield',
          '#title' => t('Social Security Number'),
          '#default_value' => $form_state['values']['ssn'],
          '#required' => TRUE,
          '#maxlength' => 9,
          '#size' => 9,
        );
      }
      else{
        $visa = sonisweb_integration_dropbox_to_form_api_options_array(
                sonisweb_integration_api("CFC.visa", "visa_drop", "no", array(array('sonis_ds', '#sonis.ds#'),
                                         array('allow_blank', "yes"),
                                         array('multi_select', "no"),
                                         array('hide', "no"))));
        $visa['AppliedFor'] = 'Visa Applied For';

        $form['Birthplace_Information']['number'] = array(
          '#type' => 'textfield',
          '#title' => t('Permanent Resident Number'),
          '#default_value' => $form_state['values']['number'],
          '#required' => FALSE,
          '#maxlength' => 50,
          '#size' => 35,
        );
        $form['Birthplace_Information']['visa'] = array(
        '#type' => 'select',
        '#title' => t('Current Visa Status'),
        '#default_value' => $form_state['values']['visa'],
        '#description' => "FHCHS is currently accepting limited applicants requiring an F visa.",
        '#options' => $visa,
        '#required' => FALSE,
        );
        /*$form['Birthplace_Information']['ssn'] = array(
          '#type' => 'textfield',
          '#title' => t('Social Security Number'),
          '#default_value' => $form_state['values']['ssn'],
          '#required' => FALSE,
          '#maxlength' => 9,
          '#size' => 9,
        );*/
      }
    }
    else {
      $form['Birthplace_Information']['ssn'] = array(
        '#type' => 'textfield',
        '#title' => t('Social Security Number'),
        '#default_value' => $form_state['values']['ssn'],
        '#required' => FALSE,
        '#maxlength' => 9,
        '#size' => 9,
      );
    }

  }
  $form['Submit'] = array(
  '#type' => 'submit',
  '#value' => t('Save and Continue'),
  );
  $form['Logout'] = array(
  '#type' => 'submit',
  '#value' => t('Save and Return Later'),
  '#prefix' => '<div class="button_secondary">',
  '#suffix' => '</div>',
  );
  return ($form);
}

function application_form_page1_validate($form, &$form_state) {
  if ($form_state['values']['ssn'] != "" && (!is_numeric($form_state['values']['ssn']) ||
      strlen($form_state['values']['ssn']) != 9)) {
    form_set_error('ssn', t("Please enter a valid Social Security Number"));
  }
  if ($form_state['values']['number'] != "" && strlen($form_state['values']['number']) < 10) {
    form_set_error('number', t("Please enter a valid Permanent Resident Number"));
  }
 /* if (substr($form_state['values']['dateofbirth'], 0, 4) >= (date("Y") - 10) ||
      substr($form_state['values']['dateofbirth'], 0, 4) <= (date("Y") - 100)) {
    form_set_error('dateofbirth', t("Please enter a valid Date of Birth"));
  }*/
}
function application_form_page1_submit($form, &$form_state) {
  global $user;
  date_default_timezone_set('UTC');
  $name = ($form_state['values']['preferred'] == ""?$form_state['values']['first']:$form_state['values']['preferred']);
  $dob = $form_state['values']['dateofbirth']['year'] .'-'. $form_state['values']['dateofbirth']['month'] .'-'. $form_state['values']['dateofbirth']['day'] .' 00:00:00';
  //$dob = $form_state['values']['dateofbirth'];
  //null values are interperted to 0 by the db_query sql injection fixing this makes it difficult to leave GED date NULL an arbitrary date (1/1/1800) was chosen by the developer to represent lack of GED NULL values
  $GED_date = '1899-12-30 00:00:00';
  
  
  if ($form_state['values']['language'] == 'I prefer not to share.') {
    $form_state['values']['language'] = 'U';
  } 
  if ($form_state['values']['ssn'] != NULL) {
    $ssn = $form_state['values']['ssn'];
  }
  else {
    $ssn = '';
  }
//
//   print_r($form);
//   print_r($form_state);
//   exit;

  $felony = $form_state['values']['felony'];

  $a = "SELECT count(Student_StudentID) as count FROM {application_Biographic} WHERE Student_StudentID = '%s'";
  $a = db_fetch_array(db_query($a, $user->uid));

  if ($a['count'] > 0) {
    $biographic_sql = "UPDATE {application_Biographic} SET Statistics_Native_English = '%s', Statistics_Native_Language = '%s', Student_Nickname = '%s', Student_Fname = '%s', Student_Mname = '%s', Student_Lname = '%s', Student_FormerLname = '%s', Student_DOB = '%s', Student_SSN = '%s', Birth_Country = '%s', Birth_City = '%s', Birth_State = '%s', Felony = '%d', Citizenship_Country = '%s', Citizenship_ID_Number = '%s', Citizenship_ID_Type = '%s', Citizenship_Visa_Status = '%s' WHERE  Student_StudentID = '%s'";
    db_query($biographic_sql, $form_state['values']['language'], $form_state['values']['nativelanguage'], $form_state['values']['preferred'], $form_state['values']['first'], $form_state['values']['middle'], $form_state['values']['last'], $form_state['values']['former_last'], $dob , $ssn, $form_state['values']['countryofbirth'], $form_state['values']['cityofbirth'], $form_state['values']['stateofbirth'], $felony, $form_state['values']['countryofcitizenship'], $form_state['values']['number'], $form_state['values']['numberquestion'], $form_state['values']['visa'], $user->uid);
  }
  else {
    $biographic_sql = "INSERT into {application_Biographic} (Student_StudentID, Statistics_Native_English, Statistics_Native_Language, Student_Nickname, Student_Fname, Student_Mname, Student_Lname, Student_FormerLname, Student_DOB, Student_SSN, Birth_Country, Birth_City, Birth_State, Felony = '%d', Citizenship_Country, Citizenship_ID_Number, Citizenship_ID_Type, Citizenship_Visa_Status, HighSchool_Name, HighSchool_Country, HighSchool_State, HighSchool_City, HighSchool_Attendance, HighSchool_Sonis_ID, GED_Testing_Site, GED_Date_Of_Issue, Statistics_Gender, Statistics_Hispanic, Statistics_Ethnic_Origin, Statistics_Native_English, Statistics_Native_Language, Statistics_Marital_Status, Statistics_Religious_Affiliation, Statistics_Home_Church, Statistics_Home_Church_City, Statistics_Home_Church_State, Personal_Statement_Agreement, Application_Started)VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%d', '%s', '%s', '%s', '%s', '%d', '%s', '%d', '%s', '%s', '%s', '%s', '%s', '%s', '%d', '%s')";
    db_query($biographic_sql, $user->uid, $form_state['values']['language'], $form_state['values']['nativelanguage'], $form_state['values']['preferred'], $form_state['values']['first'], $form_state['values']['middle'], $form_state['values']['last'], $form_state['values']['former_last'], $dob , $ssn, $form_state['values']['countryofbirth'], $form_state['values']['cityofbirth'], $form_state['values']['stateofbirth'], $felony, $form_state['values']['countryofcitizenship'], $form_state['values']['number'], $form_state['values']['numberquestion'], $form_state['values']['visa'], '', '', '', '', '', '', '', $GED_date, '', '', '', '', '', '', '', '', '', '', 0, date("Y-m-d H:i:s"));

    //Fire Application Started Trigger
    //This will never be called due to preempt in load_defaults below.
    module_invoke_all('application_changed', 'start', $user);
  }
  
  
  $a = "SELECT count(Student_StudentID) as count FROM {application_Address} WHERE Student_StudentID = '%s'";
  $a = db_fetch_array(db_query($a, $user->uid));

  if ($a['count'] > 0) {
    $address_sql = "UPDATE {application_Address} SET Country = '%s', State = '%s', City = '%s', Postal = '%s', Street = '%s', Primary_phone = '%s', Mobile_phone = '%s', Alternate_phone = '%s', Email = '%s', Contact_Name = '%s' WHERE Student_StudentID = '%s' and Type = '%s'";
    db_query($address_sql, $form_state['values']['countryofresidence'], $form_state['values']['state'],   $form_state['values']['addresscity'], $form_state['values']['postalcode'], $form_state['values']['streetaddress'], $form_state['values']['primaryphone'], $form_state['values']['cellphone'], $form_state['values']['alternatephone'], $form_state['values']['email'], $form_state['values']['preferred'], $user->uid, 'Pref Add');
  }
  else {
    $address_sql = "INSERT into {application_Address} (Student_StudentID, Country, State, City, Postal, Street, Primary_phone, Mobile_phone, Alternate_phone, Email, Type, Contact_Name)VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')";
    db_query($address_sql, $user->uid, $form_state['values']['countryofresidence'], $form_state['values']['state'],   $form_state['values']['addresscity'], $form_state['values']['postalcode'], $form_state['values']['streetaddress'], $form_state['values']['primaryphone'], $form_state['values']['cellphone'], $form_state['values']['alternatephone'], $form_state['values']['email'], 'Pref Add', $form_state['values']['preferred']);
  }

  //Enter authorized person one
  $authorize_person1 = "SELECT person_id, Student_StudentID, first_name, last_name, relationship FROM {application_authorize_person} WHERE Student_StudentID = '%s' AND first_name = '%s' AND last_name = '%s'";
  $authorize_person1 = db_fetch_array(db_query($authorize_person1, $user->uid, $form_state['values']['person1_first_name'], $form_state['values']['person1_last_name']));
  
  if (!empty($authorize_person1)) {
    
    $authorized_sql = "UPDATE {application_authorize_person} SET first_name = '%s', last_name = '%s', relationship = '%s' WHERE Student_StudentID = '%s' and person_id = '%s'";
    db_query($authorized_sql, $form_state['values']['person1_first_name'], $form_state['values']['person1_last_name'],$form_state['values']['person1_relationship'], $user->uid, $authorize_person1['person_id'] ); 
    
  }
  else {
    
     $authorized_sql = "INSERT into {application_authorize_person} (Student_StudentID, first_name, last_name, relationship)
                        VALUES('%s', '%s', '%s', '%s')";
     db_query($authorized_sql, $user->uid, $form_state['values']['person1_first_name'], $form_state['values']['person1_last_name'],$form_state['values']['person1_relationship']); 
    
  }
  
  //Enter authorized person two
  $authorize_person2 = "SELECT person_id, Student_StudentID, first_name, last_name, relationship FROM {application_authorize_person} WHERE Student_StudentID = '%s' AND first_name = '%s' AND last_name = '%s'";
  $authorize_person2 = db_fetch_array(db_query($authorize_person2, $user->uid, $form_state['values']['person2_first_name'], $form_state['values']['person2_last_name']));
  
  if (!empty($authorize_person2)) {
    
    $authorized_sql = "UPDATE {application_authorize_person} SET first_name = '%s', last_name = '%s', relationship = '%s' WHERE Student_StudentID = '%s' and person_id = '%s'";
    db_query($authorized_sql, $form_state['values']['person2_first_name'], $form_state['values']['person2_last_name'],$form_state['values']['person2_relationship'], $user->uid, $authorize_person1['person_id'] ); 
    
  }
  else {
    
     $authorized_sql = "INSERT into {application_authorize_person} (Student_StudentID, first_name, last_name, relationship)
                        VALUES('%s', '%s', '%s', '%s')";
     db_query($authorized_sql, $user->uid, $form_state['values']['person2_first_name'], $form_state['values']['person2_last_name'],$form_state['values']['person2_relationship']); 
    
  }
  
  
  //Fire Application Updated Trigger
  module_invoke_all('application_changed', 'update', $user);

  drupal_set_message(t('%name, your Personal Information section has been saved.', array('%name' => $name)));
  if ($form_state['values']['op'] == "Save and Return Later") {
    drupal_goto('logout');
  }
  else {
    drupal_goto('application/generalcollegeapplication2');
  }
}

function _application_form_page1_load_defaults(&$form_state) {
  global $user;

  $biographic_sql = "SELECT Student_Nickname, Student_Fname, Student_Mname, Student_Lname, Student_FormerLname, Student_DOB, Student_SSN, Birth_Country, Birth_City, Birth_State, Felony, Citizenship_Country, Citizenship_ID_Number, Citizenship_ID_Type, Citizenship_Visa_Status, GED_Date_Of_Issue, Statistics_Native_English, Statistics_Native_Language FROM {application_Biographic} WHERE Student_StudentID = '%s'";
  $a = db_fetch_array(db_query($biographic_sql, $user->uid));
  
  $authorized_sql = "SELECT person_id, Student_StudentID, first_name, last_name, relationship FROM {application_authorize_person} WHERE  Student_StudentID = '%s'";
  $authorized_person = db_query($authorized_sql, $user->uid);
  
  //Setting default value for authorize person
  $counter  = 1;
  while (($row = db_fetch_array($authorized_sql)) AND $counter <= 2) {
    
    if (!isset($form_state['values']['person'.$counter.'_first_name']))
        $form_state['values']['person'.$counter.'_first_name']  = $row['first_name'];
    
    if (!isset($form_state['values']['person'.$counter.'_last_name']))
        $form_state['values']['person'.$counter.'_last_name']  = $row['last_name'];
        
    if (!isset($form_state['values']['person'.$counter.'_relationship']))
        $form_state['values']['person'.$counter.'_relationship']  = $row['relationship'];      
    
    $counter++;
  }
  
  
  

  if ($a) {
    $address_sql = "SELECT Country, State, City, Postal, Street, Primary_phone, Mobile_phone, Alternate_phone, Email, Type FROM {application_Address} WHERE Student_StudentID = '%s'";
    $b = db_fetch_array(db_query($address_sql, $user->uid));
    if ($b) {
      if (!isset($form_state['values']['preferred']))
        $form_state['values']['preferred']              = $a['Student_Nickname'];
      if (!isset($form_state['values']['first']))
        $form_state['values']['first']                  = $a['Student_Fname'];
      if (!isset($form_state['values']['middle']))
        $form_state['values']['middle']                 = $a['Student_Mname'];
      if (!isset($form_state['values']['last']))
        $form_state['values']['last']                   = $a['Student_Lname'];
      if (!isset($form_state['values']['former_last']))
        $form_state['values']['former_last']             = $a['Student_FormerLname'];
       if (!isset($form_state['values']['dateofbirth'])) {
         $dob                                            = strtotime($a['Student_DOB']);
         /*$dob = split("-", $dob);
         $form_state['values']['dateofbirth']['year'] = $dob[0];
         $form_state['values']['dateofbirth']['month'] = $dob[1];
         $dob = split(" ", $dob[2]);
         $form_state['values']['dateofbirth']['day'] = $dob[0];*/
				 $form_state['values']['dateofbirth']['year'] = date('Y', $dob);
         $form_state['values']['dateofbirth']['month'] = date('n', $dob);
         $form_state['values']['dateofbirth']['day'] = date('j', $dob);
       }
//      if (!isset($form_state['values']['dateofbirth']) || substr($form_state['values']['dateofbirth'], 0, 1) == 0) {
//         $dob                                            = $a['Student_DOB'];
//         $dob = split("-", $dob);
//         $tmpa = $dob[0];
//         $tmpb = $dob[1];
//         $dob = split(" ", $dob[2]);
//         $form_state['values']['dateofbirth'] = $tmpb ."/". $dob[0] ."/". $tmpa ." ". $dob[1];
//				 $form_state['values']['dateofbirth']             = $a['Student_DOB'];
//      }
      if (!isset($form_state['values']['ssn'])) {
        if ($a['Student_SSN'] == 0)
          $form_state['values']['ssn']                  = "";
        else
          $form_state['values']['ssn']                  = $a['Student_SSN'];
      }
      if (!isset($form_state['values']['countryofbirth']))
        $form_state['values']['countryofbirth']         = $a['Birth_Country'];
      if (!isset($form_state['values']['cityofbirth']))
        $form_state['values']['cityofbirth']            = $a['Birth_City'];
      if (!isset($form_state['values']['stateofbirth']))
        $form_state['values']['stateofbirth']           = $a['Birth_State'];
      if (!isset($form_state['values']['felony']))
        $form_state['values']['felony']                 = $a['Felony'];
      if (!isset($form_state['values']['countryofcitizenship']))
        $form_state['values']['countryofcitizenship']   = $a['Citizenship_Country'];
      if (!isset($form_state['values']['number']))
        $form_state['values']['number']                 = $a['Citizenship_ID_Number'];
      if (!isset($form_state['values']['numberquestion']))
        $form_state['values']['numberquestion']         = $a['Citizenship_ID_Type'];
      if (!isset($form_state['values']['visa']))
        $form_state['values']['visa']                   = $a['Citizenship_Visa_Status'];
      if (!isset($form_state['values']['countryofresidence']))
        $form_state['values']['countryofresidence']     = $b['Country'];
      if (!isset($form_state['values']['state']))
        $form_state['values']['state']                  = $b['State'];
      if (!isset($form_state['values']['addresscity']))
        $form_state['values']['addresscity']            = $b['City'];
      if (!isset($form_state['values']['postalcode']))
        $form_state['values']['postalcode']             = $b['Postal'];
      if (!isset($form_state['values']['streetaddress']))
        $form_state['values']['streetaddress']          = $b['Street'];
      if (!isset($form_state['values']['primaryphone']))
        $form_state['values']['primaryphone']           = $b['Primary_phone'];
      if (!isset($form_state['values']['cellphone']))
        $form_state['values']['cellphone']              = $b['Mobile_phone'];
      if (!isset($form_state['values']['alternatephone']))
        $form_state['values']['alternatephone']         = $b['Alternate_phone'];
      if (!isset($form_state['values']['email']))
        $form_state['values']['email']                  = $b['Email'];
      if (!isset($form_state['values']['preferred']))
        $form_state['values']['preferred']              = $b['Type'];
      if (!isset($form_state['values']['language']))
        $form_state['values']['language']               = $a['Statistics_Native_English'];
      if (!isset($form_state['values']['nativelanguage']))
        $form_state['values']['nativelanguage']         = $a['Statistics_Native_Language'];
    }
  }
  else {
    $address_sql = "INSERT into {application_Biographic} (Student_StudentID, Student_DOB, Application_Started) VALUES ('%s', '1899-12-31', '%s')";
    db_query($address_sql, $user->uid, date("Y-m-d H:i:s"));
    
    //Fire Application Started Trigger
    module_invoke_all('application_changed', 'start', $user);
 }
}
