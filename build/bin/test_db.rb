gem 'bigdecimal', '~> 1.1'
require 'active_record'
require 'activeuuid'
require 'awesome_print'

=begin
ActiveRecord::Base.establish_connection :adapter => "mysql",
    :host => "rds1m2iqskhitpx6nmx7u.mysql.rds.aliyuncs.com",
    :database => "english",
    :username => "jiyuhang",
    :password => "jiyuhang8757871"
=end
ActiveRecord::Base.establish_connection :adapter => "sqlite3",
    :database => "timefriend.db"
class Eventtime < ActiveRecord::Base
    self.table_name = 'eventtime'
    include ActiveUUID::UUID
    natural_key :eventimeid, :typesid
    has_one :types
end
class Types < ActiveRecord::Base
    include ActiveUUID::UUID
    natural_key :typesid
    belongs_to :eventime
end
Eventtime.all.each do |et|
    tp =  et.typeid
    ap Types.find(et.typeid).typename
    ap et
end
